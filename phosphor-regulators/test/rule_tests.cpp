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
#include "rule.hpp"

#include <gtest/gtest.h>

using namespace phosphor::power::regulators;

TEST(RuleTests, Constructor)
{
    Rule rule("set_voltage_rule");
    EXPECT_EQ(rule.getID(), "set_voltage_rule");
}

TEST(RuleTests, GetID)
{
    Rule rule("read_sensor_values");
    EXPECT_EQ(rule.getID(), "read_sensor_values");
}
