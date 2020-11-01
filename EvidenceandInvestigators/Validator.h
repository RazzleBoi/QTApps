#pragma once
#include "domain.h"

class validatorError : public exception
{
private:
	string message;
public:
	validatorError(const std::string& message) : message(message) {}
	virtual const char* what() const noexcept override
	{
		return message.c_str();
	}
};
class tapeValidator
{
public:
	/// <summary>
	/// returns 1 if the given arguments sufice for creating a tape(valid date and footagePreview must have ".mp4" in the end)
	/// returns 0 otherwise
	/// </summary>
	bool validateTape(Tape tapeToBeValidated);
};


