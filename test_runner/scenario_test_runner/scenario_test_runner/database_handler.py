#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# Copyright 2020 Autoware Foundation. All rights reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

import pathlib
import sys

from scenario_test_utility.logger import Logger
from scenario_test_utility.manager import Manager
from scenario_test_utility.regex import resolve_ros_package
from scenario_test_utility.workflow_validator import WorkflowValidator
import yamale


class DatabaseHandler():

    @staticmethod
    def read_database(workflow_file, log_directory):
        Logger.print_separator('Reading workflow')
        workflow_path = ''
        if pathlib.Path(workflow_file).is_absolute():
            workflow_path = workflow_file
        else:
            workflow_path = resolve_ros_package(workflow_file)
        try:
            validator = WorkflowValidator()
            validator.validate_workflow_file(workflow_path)
        except yamale.yamale_error.YamaleError:
            import traceback
            Logger.print_error('workflow file is not valid, shutting down')
            Logger.print_error(traceback.format_exc())
            sys.exit(1)
        database = Manager.read_data(workflow_path)
        if pathlib.Path(log_directory).is_absolute():
            log_path = log_directory
        else:
            log_path = resolve_ros_package(log_directory)
        scenarios = []
        for scenario in database['Scenario']:
            scenario_path = ''
            if pathlib.Path(scenario['path']).is_absolute():
                scenario_path = scenario['path']
            else:
                scenario_path = resolve_ros_package(scenario['path'])
            Manager.check_existence(scenario_path)
            scenario['path'] = scenario_path
            scenarios.append(scenario)
        Logger.print_info('DEBUG!')
        Logger.print_info(__file__)
        Logger.print_info(pathlib.Path(__file__))
        Logger.print_info(pathlib.Path(__file__).resolve())
        Logger.print_info(pathlib.Path(__file__).resolve().parent)
        Logger.print_info(pathlib.Path(__file__).resolve().parent.parent)
        launcher_package_path = pathlib.Path(__file__).resolve().parent.parent
        return launcher_package_path, log_path, scenarios


if __name__ == '__main__':
    pass