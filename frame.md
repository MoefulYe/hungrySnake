main.c主界面1.开始游戏2.显示帮助3.显示相关信息4.排行榜5.其他退出

menu.c

help.c

about.c

rank.c

game

​	game.c游戏运行

​	地图的大小长宽用宏定义

​	初始化地图	

​	位移键

​	

​	snake

​		snake.c定义蛇结构体和方法

​		蛇 speed

​				蛇身长度length(分数)

​				蛇身节点node包含坐标

​				蛇头方向	`

​		方法

​			初始化

​			移动

​			侦测墙壁

​			侦测食物

​			速度控制

​			改变方向
           变大
​	food

​		food.c定义食物结构体和方法

​		食物结构体包含坐标和分数

​		生成食物方法

​	barrier

​		barrier.c

util

​	util.c提供基本工具如移动光标清屏暂停...	

​	隐藏光标

sql

​	sql.c实现与数据库的交互显示排行榜信息