# include <Siv3D.hpp>
# include "3D.hpp"

void Main()
{
	TDLib::D3 D;

	for (int32 i = -2; i <= 2; ++i)
		for (int32 j = -2; j <= 2; ++j)
			D.add(std::make_shared<TDLib::Cube>(Vec3(i, j, 0) * 100, 100));

	while (System::Update())
	{
		ClearPrint();
		D.update();
		D.draw();
	}
}
