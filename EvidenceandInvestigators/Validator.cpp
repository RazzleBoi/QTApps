#include "Validator.h"



bool tapeValidator::validateTape(Tape tapeToBeValidated){
	date dateOfTape = tapeToBeValidated.getDateAsInts();
	if (dateOfTape.day < 0 || dateOfTape.day> 31)
		throw validatorError("Invalid day format!");

	if (dateOfTape.month < 0 || dateOfTape.month > 12)
		throw validatorError("Invalid month format!");


	if (dateOfTape.year < 1000 || dateOfTape.year>2020)
		throw validatorError("Invalid year!");

	return 1;
}
