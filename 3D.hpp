#pragma once
# include <Siv3D.hpp>
# include "Graph.hpp"

namespace TDLib 
{
	struct View
	{
		Vec3 pos;
		double angle_horizontal;
		double angle_vertical;
		double rate;
		View();
	};

	class VecS3 : public Vec3
	{
	public:
		double r;
		double theta;
		double phi;
	};

	using Graph2 = Graph<Vec2>;
	using Graph3 = Graph<Vec3>;

	class Solid 
	{
	protected:
		Graph3 m_vertex;
		mutable Graph2 m_vertex_updated;
	public:
		Solid(Graph3 vertex);
	public:
		virtual void update(View view);
		virtual void draw() const;
	};

	class Line : public Solid
	{
	public:
		Line(Vec3 r1, Vec3 r2);
	public:
		Graph3 gen(Vec3 r1, Vec3 r2);
	};

	class Cube : public Solid
	{
	public:
		Cube(Vec3 r1, double l);
	public:
		Graph3 gen(Vec3 r1, double l);
	};

	using SolidPtr = std::shared_ptr<Solid>;

	class D3
	{
	private:
		View m_view;
		Array<SolidPtr> m_solid;
	private:
		Vec2 m_mouse;
	public:
		D3();
	public:
		void add(SolidPtr ptr);
	public:
		void update();
		void draw() const;
	};
}
