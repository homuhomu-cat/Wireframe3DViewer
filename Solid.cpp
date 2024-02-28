# include "3D.hpp"

namespace TDLib 
{
	Solid::Solid(Graph3 vertex) : m_vertex(vertex)
	{
		for (auto itr = m_vertex.node_begin(); itr != m_vertex.node_end(); ++itr)
			m_vertex_updated.add(Vec2());

		for (auto itr = m_vertex.edge_begin(); itr != m_vertex.edge_end(); ++itr)
		{
			std::pair<int32, int32> p(m_vertex.find(itr->first), m_vertex.find(itr->second));
			m_vertex_updated.connect(m_vertex_updated.node_at(p.first), m_vertex_updated.node_at(p.second));
		}
	}

	void Solid::update(View view)
	{
		static Vec2 center(400, 300);
		for (auto itr = m_vertex.node_begin(); itr != m_vertex.node_end(); ++itr)
		{
			int32 i = m_vertex.find(&(*itr));
			Vec3 r1(*itr - view.pos);
			Vec3 r2(r1.x * cos(view.angle_horizontal) + r1.z * sin(view.angle_horizontal), r1.y, -r1.x * sin(view.angle_horizontal) + r1.z * cos(view.angle_horizontal));
			Vec3 r3(r2.x, -r2.z * sin(view.angle_vertical) + r2.y * cos(view.angle_vertical), r2.z * cos(view.angle_vertical) + r2.y * sin(view.angle_vertical));
			*m_vertex_updated.node_at(i) = Vec2(r3.x, r3.y) + center;
		}
	}

	void Solid::draw() const
	{
		for (auto itr = m_vertex_updated.node_begin(); itr != m_vertex_updated.node_end(); ++itr)
			Circle(*itr, 5).draw(Palette::Red);
		for (auto itr = m_vertex_updated.edge_begin(); itr != m_vertex_updated.edge_end(); ++itr)
			s3d::Line(*(itr->first), *(itr->second)).draw(2, Palette::Red);
	}

	Line::Line(Vec3 r1, Vec3 r2) : Solid(gen(r1, r2)) {}

	Graph3 Line::gen(Vec3 r1, Vec3 r2)
	{
		Graph3 graph;
		graph.add(r1);
		graph.add(r2);
		graph.connect(graph.find(r1), graph.find(r2));
		return graph;
	}

	Cube::Cube(Vec3 r1, double l) : Solid(gen(r1, l)) {}

	Graph3 Cube::gen(Vec3 r1, double l)
	{
		Graph3 graph;
		Array<Vec3> r;
		r << r1;
		r << r1 + Vec3(l, 0, 0);
		r << r1 + Vec3(0, l, 0);
		r << r1 + Vec3(l, l, 0);
		r << r1 + Vec3(0, 0, l);
		r << r1 + Vec3(l, 0, l);
		r << r1 + Vec3(0, l, l);
		r << r1 + Vec3(l, l, l);
		for(auto itr = r.begin(); itr != r.end(); ++itr)
			graph.add(*itr);
		graph.connect(graph.find(r[0]), graph.find(r[1]));
		graph.connect(graph.find(r[0]), graph.find(r[2]));
		graph.connect(graph.find(r[3]), graph.find(r[1]));
		graph.connect(graph.find(r[3]), graph.find(r[2]));
		graph.connect(graph.find(r[4]), graph.find(r[5]));
		graph.connect(graph.find(r[4]), graph.find(r[6]));
		graph.connect(graph.find(r[7]), graph.find(r[5]));
		graph.connect(graph.find(r[7]), graph.find(r[6]));
		graph.connect(graph.find(r[0]), graph.find(r[4]));
		graph.connect(graph.find(r[1]), graph.find(r[5]));
		graph.connect(graph.find(r[2]), graph.find(r[6]));
		graph.connect(graph.find(r[3]), graph.find(r[7]));
		return graph;
	}
}
