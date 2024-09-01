#pragma once
#include <ruckig/input_parameter.hpp>
#include <ruckig/output_parameter.hpp>
#include <ruckig/ruckig.hpp>

/*
 * @brief Interpolator1D class for 1D interpolation using Ruckig algorithm
 *
 */
class Interpolator1D
{
public:
    struct State
    {
        double position;
        double velocity;
        double acceleration;

        void pass_to_input(ruckig::InputParameter<1>& input) const
        {
            input.current_position[0] = position;
            input.current_velocity[0] = velocity;
            input.current_acceleration[0] = acceleration;
        }

        void get_from_output(const ruckig::OutputParameter<1>& output)
        {
            position = output.new_position[0];
            velocity = output.new_velocity[0];
            acceleration = output.new_acceleration[0];
        }
    };

    Interpolator1D(double cycle_time, ruckig::ControlInterface control_interface): otg_{cycle_time}
    {
        input_.control_interface = control_interface;
    }
    explicit Interpolator1D(ruckig::ControlInterface control_interface)
    {
        input_.control_interface = control_interface;
    }

    void SetCycleTime(double cycle_time)
    {
        otg_.delta_time = cycle_time;
    }

    void SetTargetState(const State& target_state)
    {
        input_.target_position[0] = target_state.position;
        input_.target_velocity[0] = target_state.velocity;
        input_.target_acceleration[0] = target_state.acceleration;
    }

    void SetTargetPosition(double target_position)
    {
        input_.target_position[0] = target_position;
    }

    void SetTargetVelocity(double target_velocity)
    {
        input_.target_velocity[0] = target_velocity;
    }

    void SetTargetAcceleration(double target_acceleration)
    {
        input_.target_acceleration[0] = target_acceleration;
    }

    ruckig::Result Update(const State& current_state, State& next_state, double& next_time)
    {
        current_state.pass_to_input(input_);
        const auto result = otg_.update(input_, output_);

        next_state.get_from_output(output_);
        next_time = output_.time;
        return result;
    }

    // Defines Getter and Setter for max_velocity, max_acceleration, max_jerk
    [[nodiscard]] double GetMaxVelocity() const noexcept
    {
        return input_.max_velocity[0];
    }

    void SetMaxVelocity(double max_velocity) noexcept
    {
        input_.max_velocity[0] = max_velocity;
    }

    [[nodiscard]] double GetMaxAcceleration() const noexcept
    {
        return input_.max_acceleration[0];
    }

    void SetMaxAcceleration(double max_acceleration) noexcept
    {
        input_.max_acceleration[0] = max_acceleration;
    }

    [[nodiscard]] double GetMaxJerk() const noexcept
    {
        return input_.max_jerk[0];
    }

    void SetMaxJerk(double max_jerk) noexcept
    {
        input_.max_jerk[0] = max_jerk;
    }

    void Reset()
    {
        otg_.reset();
        output_ = ruckig::OutputParameter<1>();
    }

private:
    ruckig::InputParameter<1> input_;
    ruckig::OutputParameter<1> output_;
    ruckig::Ruckig<1> otg_;
};


/**
 * @brief PositionInterpolator1D class for 1D position interpolation using Ruckig algorithm
 *
 * Usage:
 * \code
 *  // Initialization at very early stage when parsing configuration
 *  PositionInterpolator1D interpolator{0.01};
 *  interpolator.SetMaxVelocity(3.0);
 *  interpolator.SetMaxAcceleration(3.0);
 *  interpolator.SetMaxJerk(4.0);
 *
 *  // Begin a job
 *  interpolator.SetTargetState({5.0, 0.0, 0.0});
 *  // --- in a cyclic loop ---
 *  // Obtain current state from the system `current_state`
 *  if (<target-position-changed>){
 *      interpolator.SetTargetPosition(<new-target-position>);
 *  }
 *  PositionInterpolator1D::State next_state;
 *  interpolator.Update(current_state, next_state);
 *  // Use `next_state` to actuate the system
 *  // --- end of cyclic loop ---
 * \endcode
 */
class PositionInterpolator1D : public Interpolator1D
{
public:
    using Interpolator1D::State;

    /**
     * @brief Constructor for PositionInterpolator1D
     *
     * Initializes the PositionInterpolator1D with the given cycle time and sets the control interface to position control.
     *
     * @param cycle_time The cycle time for the interpolation.
     */
    explicit PositionInterpolator1D(double cycle_time): Interpolator1D(cycle_time, ruckig::ControlInterface::Position)
    {
    }
    PositionInterpolator1D(): Interpolator1D(ruckig::ControlInterface::Position) {}

    using Interpolator1D::SetCycleTime;
    using Interpolator1D::SetTargetState;
    using Interpolator1D::SetTargetPosition;
    using Interpolator1D::SetMaxVelocity;
    using Interpolator1D::SetMaxAcceleration;
};


/**
 * @brief VelocityInterpolator1D class for 1D velocity interpolation using Ruckig algorithm
 *
 * This class provides an interface for 1D velocity interpolation using the Ruckig algorithm.
 * It inherits from the Interpolator1D class and sets the control interface to velocity control.
 *
 * Usage:
 * \code
 *  // Initialization at very early stage when parsing configuration
 *  VelocityInterpolator1D interpolator{0.01};
 *  interpolator.SetMaxVelocity(3.0);
 *  interpolator.SetMaxAcceleration(3.0);
 *  interpolator.SetMaxJerk(4.0);
 *
 *  // Begin a job
 *  interpolator.SetTargetState({0.0, 5.0, 0.0});
 *  // --- in a cyclic loop ---
 *  // Obtain current state from the system `current_state`
 *  // Optionally, update the target state
 *  if (<target-velocity-changed>){
 *      interpolator.SetTargetVelocity(<new-target-velocity>);
 *  }
 *  VelocityInterpolator1D::State next_state;
 *  interpolator.Update(current_state, next_state);
 *  // Use `next_state` to actuate the system
 *  // --- end of cyclic loop ---
 * \endcode
 */
class VelocityInterpolator1D : public Interpolator1D
{
public:
    using Interpolator1D::State;

    /**
     * @brief Constructor for VelocityInterpolator1D
     *
     * Initializes the VelocityInterpolator1D with the given cycle time and sets the control interface to velocity control.
     *
     * @param cycle_time The cycle time for the interpolation.
     */
    explicit VelocityInterpolator1D(double cycle_time): Interpolator1D(cycle_time, ruckig::ControlInterface::Velocity)
    {
    }

    VelocityInterpolator1D(): Interpolator1D(ruckig::ControlInterface::Velocity) {}

    using Interpolator1D::SetCycleTime;
    using Interpolator1D::SetTargetState;
    using Interpolator1D::SetTargetVelocity;
    using Interpolator1D::SetMaxVelocity;
    using Interpolator1D::SetMaxAcceleration;
};
