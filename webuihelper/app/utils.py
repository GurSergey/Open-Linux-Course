from constance import config


def get_id_task_by_number(number: int):
    if number == 0:
        return config.ZERO_TASK_ID
    elif number == 1:
        return config.FIRST_TASK_ID
    elif number == 2:
        return config.SECOND_TASK_ID
    elif number == 3:
        return config.THIRD_TASK_ID
    elif number == 4:
        return config.FOURTH_TASK_ID
    elif number == 5:
        return config.FIFTH_TASK_ID
    elif number == 6:
        return config.SIXTH_TASK_ID
    elif number == 7:
        return config.SEVENTH_TASK_ID
    elif number == 8:
        return config.EIGHT_TASK_ID
    elif number == 9:
        return config.NINE_TASK_ID
