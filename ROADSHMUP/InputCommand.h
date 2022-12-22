#pragma once

// Base class for all use input. The platform level abstaction will generate a set of InputCommands
// every frame and these will be processed in the game update 
class InputCommand
{
public:

	InputCommand();
	virtual ~InputCommand() = 0;

	virtual void Execute() = 0;

};


class InputLeft: public InputCommand
{
	InputLeft();

	void Execute() override;
};

class InputRight : public InputCommand
{
	InputRight();

	void Execute() override;
};

class InputUp : public InputCommand
{
	InputUp();

	void Execute() override;
};

class InputDown : public InputCommand
{

};

class InputFire : public InputCommand
{

};
