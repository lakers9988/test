
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>

struct Room {
    std::string name;
    std::string desc;
    std::map<std::string, int> exits;
    std::string item;
    bool hasMonster = false;
};

struct Player {
    int hp = 10;
    std::vector<std::string> inventory;
    int room = 0;
};

int main() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<Room> rooms = {
        {"入口", "你在一个昏暗的入口。出口在北方。", {{"北", 1}}, "钥匙", false},
        {"大厅", "大厅里有一扇门通向东边和南边。", {{"南", 0}, {"东", 2}}, "药水", false},
        {"怪物房", "一个怪物守卫着通往终点的门。", {{"西", 1}, {"北", 3}}, "", true},
        {"终点", "你到达了终点！", {{"南", 2}}, "宝藏", false}
    };
    Player player;
    std::cout << "欢迎来到文字冒险游戏！\n";
    while (true) {
        Room &room = rooms[player.room];
        std::cout << "\n你现在在：" << room.name << "\n" << room.desc << "\n";
        if (!room.item.empty()) {
            std::cout << "你发现了一个物品：" << room.item << "\n";
        }
        if (room.hasMonster) {
            std::cout << "这里有一个怪物！\n";
            std::cout << "你要战斗吗？(y/n): ";
            std::string act;
            std::cin >> act;
            if (act == "y") {
                int monsterHp = 8;
                while (player.hp > 0 && monsterHp > 0) {
                    int playerAtk = std::rand() % 4 + 1;
                    int monsterAtk = std::rand() % 3 + 1;
                    monsterHp -= playerAtk;
                    player.hp -= monsterAtk;
                    std::cout << "你攻击怪物造成 " << playerAtk << " 点伤害，怪物剩余 " << (monsterHp > 0 ? monsterHp : 0) << " HP。\n";
                    std::cout << "怪物攻击你造成 " << monsterAtk << " 点伤害，你剩余 " << (player.hp > 0 ? player.hp : 0) << " HP。\n";
                }
                if (player.hp <= 0) {
                    std::cout << "你被怪物击败了，游戏结束！\n";
                    break;
                } else {
                    std::cout << "你击败了怪物！\n";
                    room.hasMonster = false;
                }
            } else {
                std::cout << "你逃离了怪物房。\n";
                player.room = room.exits["西"];
                continue;
            }
        }
        if (!room.item.empty()) {
            std::cout << "是否拾取物品？(y/n): ";
            std::string pick;
            std::cin >> pick;
            if (pick == "y") {
                player.inventory.push_back(room.item);
                std::cout << "你获得了：" << room.item << "\n";
                if (room.item == "药水") {
                    player.hp += 5;
                    std::cout << "你的生命值恢复到 " << player.hp << "。\n";
                }
                room.item = "";
            }
        }
        if (room.name == "终点") {
            std::cout << "你发现了宝藏，游戏胜利！\n";
            break;
        }
        std::cout << "可前往的方向：";
        for (auto &e : room.exits) {
            std::cout << e.first << " ";
        }
        std::cout << "\n请输入方向（如 北/南/东/西），或输入 bag 查看背包：";
        std::string cmd;
        std::cin >> cmd;
        if (cmd == "bag") {
            std::cout << "你的背包：";
            for (auto &item : player.inventory) std::cout << item << " ";
            std::cout << "\n生命值：" << player.hp << "\n";
            continue;
        }
        if (room.exits.count(cmd)) {
            player.room = room.exits[cmd];
        } else {
            std::cout << "没有这个方向，请重新输入。\n";
        }
    }
    return 0;
}
