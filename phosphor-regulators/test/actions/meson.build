test('phosphor-regulators-actions-tests',
     executable('phosphor-regulators-actions-tests',
                'action_environment_tests.cpp',
                'set_device_action_tests.cpp',
                dependencies: [
                    gmock,
                    gtest,
                ],
                implicit_include_directories: false,
                include_directories: [
                    phosphor_regulators_include_directories,
                    phosphor_regulators_tests_include_directories
                ]
     )
)
