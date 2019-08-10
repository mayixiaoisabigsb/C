#pragma once

enum tiletype { BORDER, I, J, L, O, S, Z, T };//方块所属
enum style { COLORFUL, COLORLESS, CLASSIC };
extern style blockstyle;

class block
{
private:
	tiletype type;//所属大方块的类型
	bool active;//是否为活跃方块
public:
	unsigned sign;//新增信号系统用于拓展，记录方块的差异
	unsigned sign2;//第二个信号
	void fix();//固定方块
	void realease();//松动方块
	void show();//展示方块
	bool getActive();//返回活跃与否
	tiletype getType();//返回方块所属类型
	block(tiletype type, bool active = 1, unsigned sign = 0, unsigned sign2 = 0);//类型，活跃与否(默认活跃，用于生成新方块)
};