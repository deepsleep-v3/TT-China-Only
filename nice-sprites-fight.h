#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <windows.h>
#include <conio.h>  // 用于_getch()函数
#include <map>

using namespace std;

// 清屏函数
void clearScreen() {
    system("cls");
}

// 延迟函数（毫秒）
void delay(int ms) {
    Sleep(ms);
}

// 招式基类
class Move {
protected:
    wstring name;       // 招式名称
    wstring description; // 招式描述
    int damage;         // 基础伤害
    int energyCost;     // 能量消耗
    
public:
    Move(wstring name, wstring description, int damage, int energyCost)
        : name(name), description(description), damage(damage), energyCost(energyCost) {}
    
    virtual ~Move() {}
    
    wstring getName() const { return name; }
    wstring getDescription() const { return description; }
    int getDamage() const { return damage; }
    int getEnergyCost() const { return energyCost; }
    
    // 执行招式
    virtual int execute(Character* user, Character* target) = 0;
};

// 普通攻击招式
class NormalAttack : public Move {
public:
    NormalAttack(wstring name, wstring description, int damage)
        : Move(name, description, damage, 0) {}
    
    int execute(Character* user, Character* target) override {
        wcout << user->getName() << L" 使用了 " << name << L"！" << endl;
        return damage;
    }
};

// 特殊技能招式
class SpecialMove : public Move {
public:
    SpecialMove(wstring name, wstring description, int damage, int energyCost)
        : Move(name, description, damage, energyCost) {}
    
    int execute(Character* user, Character* target) override {
        if (user->getEnergy() < energyCost) {
            wcout << L"能量不足！需要 " << energyCost << L" 点能量。" << endl;
            return 0;
        }
        
        user->gainEnergy(-energyCost);  // 消耗能量
        wcout << user->getName() << L" 使用了 " << name << L"！" << endl;
        return damage;
    }
};

// 超必杀技招式
class SuperMove : public Move {
public:
    SuperMove(wstring name, wstring description, int damage, int energyCost)
        : Move(name, description, damage, energyCost) {}
    
    int execute(Character* user, Character* target) override {
        if (user->getEnergy() < energyCost) {
            wcout << L"能量不足！需要 " << energyCost << L" 点能量。" << endl;
            return 0;
        }
        
        user->gainEnergy(-energyCost);  // 消耗能量
        wcout << L"\n=== 超必杀技 ===\n" << user->getName() << L" 使用了 " << name << L"！" << endl;
        return damage;
    }
};

// 角色基类
class Character {
protected:
    wstring name;           // 角色名称
    int health;            // 生命值
    int maxHealth;         // 最大生命值
    int energy;            // 能量值 (0-100)
    int attackPower;       // 基础攻击力
    bool isBlocking;       // 是否正在防御
    vector<wstring> taunts; // 嘲讽台词
    map<wstring, Move*> moves; // 招式列表
    
public:
    Character(wstring name, int health, int attackPower) 
        : name(name), health(health), maxHealth(health), 
          energy(0), attackPower(attackPower), isBlocking(false) {
        // 初始化嘲讽台词
        taunts = {
            L"就这点本事？",
            L"太弱了！",
            L"你还差得远呢！",
            L"放弃吧！",
            L"就这种程度可赢不了我！"
        };
    }
    
    virtual ~Character() {
        // 清理招式
        for (auto& pair : moves) {
            delete pair.second;
        }
    }
    
    wstring getName() const { return name; }
    int getHealth() const { return health; }
	int getMaxHealth() const { return maxHealth; }
    int getEnergy() const { return energy; }
    bool isAlive() const { return health > 0; }
    bool isBlockingState() const { return isBlocking; }
    
    // 获取所有招式名称
    vector<wstring> getMoveNames() const {
        vector<wstring> names;
        for (const auto& pair : moves) {
            names.push_back(pair.first);
        }
        return names;
    }
    
    // 获取招式
    Move* getMove(wstring moveName) const {
        auto it = moves.find(moveName);
        if (it != moves.end()) {
            return it->second;
        }
        return nullptr;
    }
    
    // 显示所有招式
    void displayMoves() const {
        wcout << L"\n=== " << name << L" 的招式 ===" << endl;
        for (const auto& pair : moves) {
            Move* move = pair.second;
            wcout << move->getName() << L" - " << move->getDescription();
            if (move->getEnergyCost() > 0) {
                wcout << L" (消耗 " << move->getEnergyCost() << L" 能量)";
            }
            wcout << endl;
        }
    }
    
    // 受到伤害
    void takeDamage(int damage) {
        if (isBlocking) {
            damage = max(1, damage / 2);  // 防御状态下伤害减半
            wcout << name << L" 成功防御！伤害减半！" << endl;
        }
        
        health = max(0, health - damage);
        
        if (damage > 0) {
            wcout << name << L" 受到 " << damage << L" 点伤害！" << endl;
            energy = min(100, energy + damage / 5);  // 受伤时积累能量
        }
    }
    
    // 恢复生命值
    void heal(int amount) {
        health = min(maxHealth, health + amount);
        wcout << name << L" 恢复了 " << amount << L" 点生命值！" << endl;
    }
    
    // 积累能量
    void gainEnergy(int amount) {
        energy = min(100, max(0, energy + amount));
        if (amount > 0) {
            wcout << name << L" 积累了能量！" << endl;
        } else if (amount < 0) {
            wcout << name << L" 消耗了能量！" << endl;
        }
    }
    
    // 显示状态
    void displayStatus() const {
        wcout << L"[" << name << L"] ";
        
        // 绘制生命条
        wcout << L"生命: [";
        int healthBars = (health * 20) / maxHealth;
        for (int i = 0; i < 20; i++) {
            wcout << (i < healthBars ? L'=' : L' ');
        }
        wcout << L"] " << health << L"/" << maxHealth << L"  ";
        
        // 绘制能量条
        wcout << L"能量: [";
        int energyBars = energy / 5;
        for (int i = 0; i < 20; i++) {
            wcout << (i < energyBars ? L'#' : L' ');
        }
        wcout << L"] " << energy << L"/100" << endl;
    }
    
    // 防御
    void block() {
        isBlocking = true;
        wcout << name << L" 进入防御状态！" << endl;
    }
    
    // 取消防御
    void unblock() {
        isBlocking = false;
    }
    
    // 随机嘲讽
    wstring getRandomTaunt() {
        return taunts[rand() % taunts.size()];
    }
    
    // 角色类型描述
    virtual wstring getTypeDescription() const = 0;
    
    // 角色入场台词
    virtual wstring getEntranceQuote() const = 0;
    
    // 角色胜利台词
    virtual wstring getVictoryQuote() const = 0;
};

// 火属性小精灵（KOF风格）
class FireFighter : public Character {
public:
    FireFighter() : Character(L"火焰战士", 1200, 80) {
        // 初始化招式
        moves[L"火焰拳"] = new NormalAttack(L"火焰拳", L"基础的火焰拳击", attackPower);
        moves[L"火焰踢"] = new NormalAttack(L"火焰踢", L"带火的飞踢", attackPower * 1.2);
        moves[L"烈焰踢"] = new SpecialMove(L"烈焰踢", L"强力的火焰飞踢", attackPower * 1.5, 30);
        moves[L"火焰风暴"] = new SuperMove(L"火焰风暴", L"召唤巨大的火焰风暴", attackPower * 3, 100);
    }
    
    wstring getTypeDescription() const override {
        return L"近距离格斗专家，擅长火焰攻击";
    }
    
    wstring getEntranceQuote() const override {
        return L"准备好被火焰吞噬了吗？";
    }
    
    wstring getVictoryQuote() const override {
        return L"这就是玩火的下场！";
    }
};

// 水属性小精灵（KOF风格）
class WaterSniper : public Character {
public:
    WaterSniper() : Character(L"水之狙击手", 1000, 100) {
        // 初始化招式
        moves[L"水箭"] = new NormalAttack(L"水箭", L"发射高压水箭", attackPower);
        moves[L"水弹"] = new NormalAttack(L"水弹", L"连续发射水弹", attackPower * 1.1);
        moves[L"水牢术"] = new SpecialMove(L"水牢术", L"用巨大的水牢困住对手", attackPower * 1.8, 30);
        moves[L"海啸风暴"] = new SuperMove(L"海啸风暴", L"召唤巨大的海啸吞没对手", attackPower * 3.5, 100);
    }
    
    wstring getTypeDescription() const override {
        return L"远程攻击专家，擅长控制和范围伤害";
    }
    
    wstring getEntranceQuote() const override {
        return L"在水中颤抖吧！";
    }
    
    wstring getVictoryQuote() const override {
        return L"你的反抗就像水滴入海！";
    }
};

// 雷属性小精灵（KOF风格）
class ThunderWarrior : public Character {
public:
    ThunderWarrior() : Character(L"雷霆战士", 900, 120) {
        // 初始化招式
        moves[L"闪电拳"] = new NormalAttack(L"闪电拳", L"带有闪电的快速拳击", attackPower);
        moves[L"雷光踢"] = new NormalAttack(L"雷光踢", L"带有闪电的强力踢击", attackPower * 1.2);
        moves[L"雷光连击"] = new SpecialMove(L"雷光连击", L"连续的闪电攻击", attackPower * 2, 30);
        moves[L"雷神降临"] = new SuperMove(L"雷神降临", L"召唤雷神之力进行毁灭性打击", attackPower * 4, 100);
    }
    
    wstring getTypeDescription() const override {
        return L"速度型战士，擅长连击和暴击";
    }
    
    wstring getEntranceQuote() const override {
        return L"感受雷电的力量吧！";
    }
    
    wstring getVictoryQuote() const override {
        return L"雷电不会两次击中同一个地方...但我会！";
    }
};

// 隐藏BOSS角色
class FrostQueen : public Character {
public:
    FrostQueen() : Character(L"冰霜", 1400, 140) {
        // 初始化嘲讽台词
        taunts.clear();  // 先清空向量（如果需要）
        taunts.push_back(L"你们将被永远冰封！");
        taunts.push_back(L"感受绝对零度的恐惧吧！");
        taunts.push_back(L"在冰狱中忏悔吧！");
        taunts.push_back(L"寒冷将吞噬你们的灵魂！");
        taunts.push_back(L"这个世界将变成一片冰原！");
        
        // 初始化招式
        moves[L"冰棱穿刺"] = new NormalAttack(L"冰棱穿刺", L"从地面刺出锋利的冰棱", attackPower);
        moves[L"寒霜冲击"] = new NormalAttack(L"寒霜冲击", L"释放寒霜能量进行冲击", attackPower * 1.3);
        moves[L"暴风雪"] = new SpecialMove(L"暴风雪", L"召唤猛烈的暴风雪攻击对手", attackPower * 2.5, 40);
        moves[L"绝对零度"] = new SuperMove(L"绝对零度", L"将周围温度降至绝对零度，造成毁灭性伤害", attackPower * 5, 120);
    }
    
    wstring getTypeDescription() const override {
        return L"？？？";
    }
    
    wstring getEntranceQuote() const override {
        return L"我将用这些精灵....统治世界！";
    }
    
    wstring getVictoryQuote() const override {
        return L"现在，知道我的厉害了吗？";
    }
};

// 战斗管理器
class BattleManager {
private:
    Character* player;
    Character* opponent;
    int round;
    bool battleOver;
    
public:
    BattleManager(Character* player, Character* opponent) 
        : player(player), opponent(opponent), round(1), battleOver(false) {}
    
    ~BattleManager() {
        // 不删除角色，因为它们由GameManager管理
    }
    
    // 显示战斗界面
    void displayBattleScreen() {
        clearScreen();
        
        wcout << L"=== 第 " << round << L" 回合 ===" << endl;
        wcout << L"[" << player->getName() << L"] VS [" << opponent->getName() << L"]" << endl;
        wcout << L"----------------------------------------" << endl;
        
        // 显示玩家状态
        wcout << L"你: ";
        player->displayStatus();
        
        // 显示对手状态
        wcout << L"\n对手: ";
        opponent->displayStatus();
        
        wcout << L"----------------------------------------" << endl;
    }
    
    // 玩家回合
    void playerTurn() {
        displayBattleScreen();
        wcout << L"\n--- 你的回合 ---" << endl;
        
        player->unblock();  // 回合开始取消防御
        
        while (true) {
            wcout << L"\n选择行动:" << endl;
            wcout << L"1. 查看招式列表" << endl;
            wcout << L"2. 使用招式" << endl;
            wcout << L"3. 防御" << endl;
            wcout << L"4. 嘲讽对手" << endl;
            
            int choice;
            do {
                wcout << L"输入选择 (1-4): ";
                wcin >> choice;
                wcin.ignore();  // 清除输入缓冲区
            } while (choice < 1 || choice > 4);
            
            switch (choice) {
                case 1: {  // 查看招式列表
                    player->displayMoves();
                    wcout << L"\n按Enter继续..." << endl;
                    wcin.ignore();
                    wcin.get();
                    break;
                }
                
                case 2: {  // 使用招式
                    wcout << L"\n输入招式名称: ";
                    wstring moveName;
                    getline(wcin, moveName);
                    
                    Move* move = player->getMove(moveName);
                    if (move) {
                        int damage = move->execute(player, opponent);
                        if (damage > 0) {
                            opponent->takeDamage(damage);
                            
                            // 成功使用招式后积累额外能量
                            int energyGain = max(1, move->getEnergyCost() / 3);
                            player->gainEnergy(energyGain);
                        }
                        return;
                    } else {
                        wcout << L"无效的招式名称！" << endl;
                        delay(1000);
                    }
                    break;
                }
                
                case 3: {  // 防御
                    player->block();
                    wcout << L"你进入了防御状态！" << endl;
                    delay(1500);
                    return;
                }
                
                case 4: {  // 嘲讽
                    wcout << player->getName() << L": " << player->getRandomTaunt() << endl;
                    delay(1000);
                    
                    // 对手可能被激怒，攻击命中率降低
                    wcout << opponent->getName() << L" 被激怒了！" << endl;
                    delay(1000);
                    break;
                }
            }
        }
    }
    
    // 对手回合
    void opponentTurn() {
        displayBattleScreen();
        wcout << L"\n--- 对手回合 ---" << endl;
        delay(1000);
        
        opponent->unblock();  // 回合开始取消防御
        
        // 对手AI决策
        vector<wstring> availableMoves = opponent->getMoveNames();
        vector<wstring> validMoves;
        
        // 筛选出能量足够的招式
        for (const auto& moveName : availableMoves) {
            Move* move = opponent->getMove(moveName);
            if (move && opponent->getEnergy() >= move->getEnergyCost()) {
                validMoves.push_back(moveName);
            }
        }
        
        // 如果没有足够能量的招式，只能使用普通攻击
        if (validMoves.empty()) {
            for (const auto& moveName : availableMoves) {
                Move* move = opponent->getMove(moveName);
                if (move && move->getEnergyCost() == 0) {
                    validMoves.push_back(moveName);
                }
            }
        }
        
        if (validMoves.empty()) {
            wcout << opponent->getName() << L" 因能量不足无法行动！" << endl;
            return;
        }
        
        // 根据对手生命值决定策略
        bool isDesperate = opponent->getHealth() < opponent->getMaxHealth() / 3;
        
        // 随机选择一个招式，绝望时更倾向于使用高伤害招式
        wstring chosenMove;
        if (isDesperate && opponent->getEnergy() >= 80) {
            // 绝望时优先使用超必杀技
            for (const auto& moveName : validMoves) {
                Move* move = opponent->getMove(moveName);
                if (move->getEnergyCost() >= 80) {
                    chosenMove = moveName;
                    break;
                }
            }
        }
        
        if (chosenMove.empty()) {
            // 否则随机选择
            chosenMove = validMoves[rand() % validMoves.size()];
        }
        
        Move* move = opponent->getMove(chosenMove);
        
        wcout << opponent->getName() << L" 准备使用 " << chosenMove << L"！" << endl;
        delay(1500);
        
        int damage = move->execute(opponent, player);
        if (damage > 0) {
            player->takeDamage(damage);
            
            // 成功使用招式后积累额外能量
            int energyGain = max(1, move->getEnergyCost() / 3);
            opponent->gainEnergy(energyGain);
        }
        
        delay(2000);
    }
    
    // 检查战斗是否结束
    bool checkBattleOver() {
        if (!player->isAlive()) {
            displayBattleScreen();
            wcout << L"\n=== 战斗结束 ===" << endl;
            wcout << opponent->getName() << L" 获胜！" << endl;
            wcout << opponent->getVictoryQuote() << endl;
            battleOver = true;
            return true;
        }
        
        if (!opponent->isAlive()) {
            displayBattleScreen();
            wcout << L"\n=== 战斗结束 ===" << endl;
            wcout << player->getName() << L" 获胜！" << endl;
            wcout << player->getVictoryQuote() << endl;
            battleOver = true;
            return true;
        }
        
        return false;
    }
    
    // 进行一回合战斗
    void fightRound() {
        displayBattleScreen();
        wcout << L"\n=== 回合开始 ===" << endl;
        delay(2000);
        
        // 战斗流程（严格回合制：你一回我一回）
        playerTurn();
        if (checkBattleOver()) return;
        
        opponentTurn();
        checkBattleOver();
        
        // 回合结束
        if (!battleOver) {
            round++;
            wcout << L"\n=== 回合结束 ===" << endl;
            wcout << L"按Enter进入下一回合..." << endl;
            wcin.ignore();
            wcin.get();
        }
    }
    
    // 战斗主循环
    bool startBattle() {
        // 战斗开场
        displayBattleScreen();
        wcout << L"\n=== 战斗开始 ===" << endl;
        wcout << player->getName() << L": " << player->getEntranceQuote() << endl;
        wcout << opponent->getName() << L": " << opponent->getEntranceQuote() << endl;
        wcout << L"\n3..." << endl;
        delay(1000);
        wcout << L"2..." << endl;
        delay(1000);
        wcout << L"1..." << endl;
        delay(1000);
        wcout << L"FIGHT!" << endl;
        delay(1000);
        
        // 战斗循环
        while (!battleOver) {
            fightRound();
        }
        
        // 返回战斗结果（true表示玩家胜利，false表示失败）
        return player->isAlive();
    }
};

// 剧情管理器
class StoryManager {
public:
    // 触发隐藏剧情
    static void triggerHiddenStory(Character* player) {
        clearScreen();
        
        wcout << L"" << endl;
	}
};