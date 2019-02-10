#!/usr/bin/python3

class ValidationError(Exception):
    def __init__(self, message, errors):
        # Calling the base class constructor with the parameters it needs.
        super(ValidationError, self).__init__(message)

        # My code.
        self.error = errors

try:
    raise ValidationError("Fuck! We got an exception here!")
except ValidationError :
    print("In the 'except' block!")
    exit(1)

exit(0)
