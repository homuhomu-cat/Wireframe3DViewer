# include "3D.hpp"

namespace TDLib 
{
	D3::D3() : m_mouse(Cursor::PosF()) {}

	void D3::add(SolidPtr ptr) 
	{
		m_solid << ptr;
	}

	void D3::update()
	{
		bool flag = false;

		Vec2 mouse = Cursor::PosF();
		if (m_mouse != mouse)
		{
			Vec2 mouse_r = mouse - m_mouse;
			if (MouseR.pressed())
			{
				m_view.pos.x += mouse_r.x;
				m_view.pos.y += mouse_r.y;
			}
			else
			{
				m_view.angle_horizontal -= ToRadians((mouse_r.x / 800.0) * 360);
				m_view.angle_vertical -= ToRadians((mouse_r.y / 600.0) * 360);
			}
			m_mouse = mouse;
			flag = true;
		}

		if (KeyR.down())
		{
			m_view = View();
			flag = true;
		}

		if (flag)
			for (auto itr = m_solid.begin(); itr != m_solid.end(); ++itr)
				(*itr)->update(m_view);
	}

	void D3::draw() const
	{
		Print << Format(U"(", m_view.pos.x, U",", m_view.pos.y, U",", m_view.pos.z, U",", m_view.angle_horizontal, U",", m_view.angle_vertical, U")");
		for (auto itr = m_solid.begin(); itr != m_solid.end(); ++itr)
			(*itr)->draw();
	}
}