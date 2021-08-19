#pragma once
class Position {
public:
	Position();
	~Position();
	Position(int a, int b);

	int get_x(void);
	void set_x(int a);

	int get_y(void);
	void set_y(int a);

private:
	int x, y;
};