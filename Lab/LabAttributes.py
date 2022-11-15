ERROR_ATTRIBUTES= ['domain', 
                    'problem', 
                    'algorithm', 
                    'unexplained_errors', 
                    'error', 
                    'raw_memory',
                    'p7_settings_file']

PREDEFINED_ATTRIBUTES= ['cost', 
                        'coverage', 
                        'dead_ends', 
                        'evaluations', 
                        'expansions', 
                        'generated', 
                        'initial_h_value', 
                        'plan_length', 
                        'planner_time', 
                        'search_time', 
                        'unsolvable',
                        'translator_facts',
                        'p7_solving_problem_ms',
                        'p7_validating_reformulated_plan_notes',
                        'p7_validating_rebuilded_plan_notes',
                        'p7_solving_problem_notes',
                        'p7_rebuild_sas_plan_notes',
                        'p7_parse_sas_plan_notes']

ATTRIBUTES = ERROR_ATTRIBUTES + PREDEFINED_ATTRIBUTES