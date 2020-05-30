#ifndef _BUTTON_H_
#define _BUTTON_H_
class Button{
private:
	float top;
    double left;
    double width;
    double height;

public:
	typedef void (*ClickCallback)();
  	ClickCallback onClick;

    Button(double top, double left, double width, double height, ClickCallback onClick)
    : top(top)
    , left(left)
    , width(width)
    , height(height)
    , onClick(onClick) {}

  	~Button(){}

  	void CheckClick(double x, double y) {
    if (x >= left && x <= left + width &&   // x
        y <= top && y >= top + height) {    // y
            onClick();
        }
	}
};
#endif