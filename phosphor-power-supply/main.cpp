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
#include <CLI/CLI.hpp>
#include <phosphor-logging/log.hpp>

#include <filesystem>

int main(int argc, char* argv[])
{
    using namespace phosphor::logging;

    CLI::App app{"OpenBMC Power Supply Unit Monitor"};

    std::string configfile;
    app.add_option("-c,--config", configfile, "JSON configuration file path")
        ->check(CLI::ExistingFile);

    // Read the arguments.
    CLI11_PARSE(app, argc, argv);
    if (configfile.empty())
    {
        configfile = "/etc/phosphor-psu-monitor/psu_config.json";
    }

    if (!std::filesystem::exists(configfile))
    {
        log<level::ERR>("Configuration file does not exist",
                        entry("FILENAME=%s", configfile.c_str()));
        return -1;
    }

    return 0;
}
