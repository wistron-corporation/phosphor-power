/**
 * Copyright © 2019 IBM Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#pragma once

#include "action.hpp"
#include "action_environment.hpp"

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace phosphor::power::regulators
{

/**
 * @class OrAction
 *
 * Executes a sequence of actions and tests whether any of them returned true.
 *
 * Implements the "or" action in the JSON config file.
 */
class OrAction : public Action
{
  public:
    // Specify which compiler-generated methods we want
    OrAction() = delete;
    OrAction(const OrAction&) = delete;
    OrAction(OrAction&&) = delete;
    OrAction& operator=(const OrAction&) = delete;
    OrAction& operator=(OrAction&&) = delete;
    virtual ~OrAction() = default;

    /**
     * Constructor.
     *
     * @param actions actions to execute
     */
    explicit OrAction(std::vector<std::unique_ptr<Action>> actions) :
        actions{std::move(actions)}
    {
    }

    /**
     * Executes the actions specified in the constructor.
     *
     * Returns true if any of the actions returned true, otherwise returns
     * false.
     *
     * Note: All of the actions will be executed even if an action before the
     * end returns true.  This ensures that actions with beneficial side-effects
     * are always executed, such as a register read that clears latched fault
     * bits.
     *
     * Throws an exception if an error occurs and an action cannot be
     * successfully executed.
     *
     * @param environment action execution environment
     * @return true if any actions returned true, otherwise returns false
     */
    virtual bool execute(ActionEnvironment& environment) override
    {
        bool returnValue{false};
        for (std::unique_ptr<Action>& action : actions)
        {
            if (action->execute(environment) == true)
            {
                returnValue = true;
            }
        }
        return returnValue;
    }

    /**
     * Returns the actions to execute.
     *
     * @return actions to execute
     */
    const std::vector<std::unique_ptr<Action>>& getActions() const
    {
        return actions;
    }

    /**
     * Returns a string description of this action.
     *
     * @return description of action
     */
    virtual std::string toString() const override
    {
        return "or: [ ... ]";
    }

  private:
    /**
     * Actions to execute.
     */
    std::vector<std::unique_ptr<Action>> actions{};
};

} // namespace phosphor::power::regulators
