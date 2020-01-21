#!/usr/bin/env python

import argparse
import json
import sys
import jsonschema

r"""
Validates the phosphor-regulators configuration file. Checks it against a JSON
schema as well as doing some extra checks that can't be encoded in the schema.
"""

def handle_validation_error():
    sys.exit("Validation failed.")

def check_duplicate_rule_id(config_json):
    r"""
    Check that there aren't any "rule" elements with the same 'id' field.
    config_json: Configuration file JSON
    """
    rule_ids = []
    for rule in config_json.get('rules', {}):
        rule_id = rule['id']
        if rule_id in rule_ids:
            sys.stderr.write("Error: Duplicate rule ID.\n"+\
            "Found multiple rules with the ID "+rule_id+'\n')
            handle_validation_error()
        else:
            rule_ids.append(rule_id)

def check_duplicate_chassis_number(config_json):
    r"""
    Check that there aren't any "chassis" elements with the same 'number' field.
    config_json: Configuration file JSON
    """
    numbers = []
    for chassis in config_json.get('chassis', {}):
        number = chassis['number']
        if number in numbers:
            sys.stderr.write("Error: Duplicate chassis number.\n"+\
            "Found multiple chassis with the number "+str(number)+'\n')
            handle_validation_error()
        else:
            numbers.append(number)

def check_duplicate_device_id(config_json):
    r"""
    Check that there aren't any "devices" with the same 'id' field.
    config_json: Configuration file JSON
    """
    device_ids = []
    for chassis in config_json.get('chassis', {}):
        for device in chassis.get('devices', {}):
            device_id = device['id']
            if device_id in device_ids:
                sys.stderr.write("Error: Duplicate device ID.\n"+\
                "Found multiple devices with the ID "+device_id+'\n')
                handle_validation_error()
            else:
                device_ids.append(device_id)

def check_duplicate_rail_id(config_json):
    r"""
    Check that there aren't any "rails" with the same 'id' field.
    config_json: Configuration file JSON
    """
    rail_ids = []
    for chassis in config_json.get('chassis', {}):
        for device in chassis.get('devices', {}):
            for rail in device.get('rails', {}):
                rail_id = rail['id']
                if rail_id in rail_ids:
                    sys.stderr.write("Error: Duplicate rail ID.\n"+\
                    "Found multiple rails with the ID "+rail_id+'\n')
                    handle_validation_error()
                else:
                    rail_ids.append(rail_id)

def check_for_duplicates(config_json):
    r"""
    Check for duplicate ID.
    """
    check_duplicate_rule_id(config_json)

    check_duplicate_chassis_number(config_json)

    check_duplicate_device_id(config_json)

    check_duplicate_rail_id(config_json)

def validate_schema(config, schema):
    r"""
    Validates the specified config file using the specified
    schema file.

    config:   Path of the file containing the config JSON
    schema:   Path of the file containing the schema JSON
    """

    with open(config) as config_handle:
        config_json = json.load(config_handle)

        with open(schema) as schema_handle:
            schema_json = json.load(schema_handle)

            try:
                jsonschema.validate(config_json, schema_json)
            except jsonschema.ValidationError as e:
                print(e)
                handle_validation_error()

    return config_json

if __name__ == '__main__':

    parser = argparse.ArgumentParser(
        description='phosphor-regulators configuration file validator')

    parser.add_argument('-s', '--schema-file', dest='schema_file',
                        help='The phosphor-regulators schema file')

    parser.add_argument('-c', '--configuration-file', dest='configuration_file',
                        help='The phosphor-regulators configuration file')

    args = parser.parse_args()

    if not args.schema_file:
        parser.print_help()
        sys.exit("Error: Schema file is required.")
    if not args.configuration_file:
        parser.print_help()
        sys.exit("Error: Configuration file is required.")

    config_json = validate_schema(args.configuration_file, args.schema_file)
    check_for_duplicates(config_json)