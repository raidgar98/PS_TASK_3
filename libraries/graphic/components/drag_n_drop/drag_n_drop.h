#pragma once

#include "../rectangle_component/rectangle_component.h"
#include "../wrapper/wrapper.h"

using inner_item = Wrapper<RectangleComponent>;
using arg_type = RectangleComponent *;
using ModifyMe = std::function<void(arg_type)>;
using ModifyMeAndExternal = std::function<void(arg_type,arg_type)>;
void swap_drag_n_drop(arg_type current, arg_type external);
template<typename T>
constexpr arg_type force(T val) { return dynamic_cast<arg_type>(const_cast<Component*>(val)); }

// Have to
struct DragAndDrop : public Wrapper<RectangleComponent>
{

	ModifyMe on_drag;			 // called whe grabbed
	ModifyMeAndExternal on_drop; // get element that this was dropped on

	DragAndDrop(
		RectangleComponent *comp, ModifyMeAndExternal _on_drop = [](arg_type, arg_type) { return; }, ModifyMe _on_drag = [](arg_type) { return; })
		: Wrapper{comp}, on_drag{_on_drag}, on_drop{_on_drop}
	{
	}

	virtual str name() const override { return str{str{"DragNDrop<"} + inner_item::name() + ">"}.c_str(); }

	void drag(const Point &)
	{
		on_drag(force(get_base_component(this)));
	}
	void drop(DragAndDrop *d)
	{
		on_drop(force(get_base_component(this, true)), force(get_base_component(d, true)));
	};
};
