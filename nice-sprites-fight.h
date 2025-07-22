#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <windows.h>
#include <conio.h>  // ����_getch()����
#include <map>

using namespace std;

// ��������
void clearScreen() {
    system("cls");
}

// �ӳٺ��������룩
void delay(int ms) {
    Sleep(ms);
}

// ��ʽ����
class Move {
protected:
    wstring name;       // ��ʽ����
    wstring description; // ��ʽ����
    int damage;         // �����˺�
    int energyCost;     // ��������
    
public:
    Move(wstring name, wstring description, int damage, int energyCost)
        : name(name), description(description), damage(damage), energyCost(energyCost) {}
    
    virtual ~Move() {}
    
    wstring getName() const { return name; }
    wstring getDescription() const { return description; }
    int getDamage() const { return damage; }
    int getEnergyCost() const { return energyCost; }
    
    // ִ����ʽ
    virtual int execute(Character* user, Character* target) = 0;
};

// ��ͨ������ʽ
class NormalAttack : public Move {
public:
    NormalAttack(wstring name, wstring description, int damage)
        : Move(name, description, damage, 0) {}
    
    int execute(Character* user, Character* target) override {
        wcout << user->getName() << L" ʹ���� " << name << L"��" << endl;
        return damage;
    }
};

// ���⼼����ʽ
class SpecialMove : public Move {
public:
    SpecialMove(wstring name, wstring description, int damage, int energyCost)
        : Move(name, description, damage, energyCost) {}
    
    int execute(Character* user, Character* target) override {
        if (user->getEnergy() < energyCost) {
            wcout << L"�������㣡��Ҫ " << energyCost << L" ��������" << endl;
            return 0;
        }
        
        user->gainEnergy(-energyCost);  // ��������
        wcout << user->getName() << L" ʹ���� " << name << L"��" << endl;
        return damage;
    }
};

// ����ɱ����ʽ
class SuperMove : public Move {
public:
    SuperMove(wstring name, wstring description, int damage, int energyCost)
        : Move(name, description, damage, energyCost) {}
    
    int execute(Character* user, Character* target) override {
        if (user->getEnergy() < energyCost) {
            wcout << L"�������㣡��Ҫ " << energyCost << L" ��������" << endl;
            return 0;
        }
        
        user->gainEnergy(-energyCost);  // ��������
        wcout << L"\n=== ����ɱ�� ===\n" << user->getName() << L" ʹ���� " << name << L"��" << endl;
        return damage;
    }
};

// ��ɫ����
class Character {
protected:
    wstring name;           // ��ɫ����
    int health;            // ����ֵ
    int maxHealth;         // �������ֵ
    int energy;            // ����ֵ (0-100)
    int attackPower;       // ����������
    bool isBlocking;       // �Ƿ����ڷ���
    vector<wstring> taunts; // ����̨��
    map<wstring, Move*> moves; // ��ʽ�б�
    
public:
    Character(wstring name, int health, int attackPower) 
        : name(name), health(health), maxHealth(health), 
          energy(0), attackPower(attackPower), isBlocking(false) {
        // ��ʼ������̨��
        taunts = {
            L"����㱾�£�",
            L"̫���ˣ�",
            L"�㻹���Զ�أ�",
            L"�����ɣ�",
            L"�����̶ֳȿ�Ӯ�����ң�"
        };
    }
    
    virtual ~Character() {
        // ������ʽ
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
    
    // ��ȡ������ʽ����
    vector<wstring> getMoveNames() const {
        vector<wstring> names;
        for (const auto& pair : moves) {
            names.push_back(pair.first);
        }
        return names;
    }
    
    // ��ȡ��ʽ
    Move* getMove(wstring moveName) const {
        auto it = moves.find(moveName);
        if (it != moves.end()) {
            return it->second;
        }
        return nullptr;
    }
    
    // ��ʾ������ʽ
    void displayMoves() const {
        wcout << L"\n=== " << name << L" ����ʽ ===" << endl;
        for (const auto& pair : moves) {
            Move* move = pair.second;
            wcout << move->getName() << L" - " << move->getDescription();
            if (move->getEnergyCost() > 0) {
                wcout << L" (���� " << move->getEnergyCost() << L" ����)";
            }
            wcout << endl;
        }
    }
    
    // �ܵ��˺�
    void takeDamage(int damage) {
        if (isBlocking) {
            damage = max(1, damage / 2);  // ����״̬���˺�����
            wcout << name << L" �ɹ��������˺����룡" << endl;
        }
        
        health = max(0, health - damage);
        
        if (damage > 0) {
            wcout << name << L" �ܵ� " << damage << L" ���˺���" << endl;
            energy = min(100, energy + damage / 5);  // ����ʱ��������
        }
    }
    
    // �ָ�����ֵ
    void heal(int amount) {
        health = min(maxHealth, health + amount);
        wcout << name << L" �ָ��� " << amount << L" ������ֵ��" << endl;
    }
    
    // ��������
    void gainEnergy(int amount) {
        energy = min(100, max(0, energy + amount));
        if (amount > 0) {
            wcout << name << L" ������������" << endl;
        } else if (amount < 0) {
            wcout << name << L" ������������" << endl;
        }
    }
    
    // ��ʾ״̬
    void displayStatus() const {
        wcout << L"[" << name << L"] ";
        
        // ����������
        wcout << L"����: [";
        int healthBars = (health * 20) / maxHealth;
        for (int i = 0; i < 20; i++) {
            wcout << (i < healthBars ? L'=' : L' ');
        }
        wcout << L"] " << health << L"/" << maxHealth << L"  ";
        
        // ����������
        wcout << L"����: [";
        int energyBars = energy / 5;
        for (int i = 0; i < 20; i++) {
            wcout << (i < energyBars ? L'#' : L' ');
        }
        wcout << L"] " << energy << L"/100" << endl;
    }
    
    // ����
    void block() {
        isBlocking = true;
        wcout << name << L" �������״̬��" << endl;
    }
    
    // ȡ������
    void unblock() {
        isBlocking = false;
    }
    
    // �������
    wstring getRandomTaunt() {
        return taunts[rand() % taunts.size()];
    }
    
    // ��ɫ��������
    virtual wstring getTypeDescription() const = 0;
    
    // ��ɫ�볡̨��
    virtual wstring getEntranceQuote() const = 0;
    
    // ��ɫʤ��̨��
    virtual wstring getVictoryQuote() const = 0;
};

// ������С���飨KOF���
class FireFighter : public Character {
public:
    FireFighter() : Character(L"����սʿ", 1200, 80) {
        // ��ʼ����ʽ
        moves[L"����ȭ"] = new NormalAttack(L"����ȭ", L"�����Ļ���ȭ��", attackPower);
        moves[L"������"] = new NormalAttack(L"������", L"����ķ���", attackPower * 1.2);
        moves[L"������"] = new SpecialMove(L"������", L"ǿ���Ļ������", attackPower * 1.5, 30);
        moves[L"����籩"] = new SuperMove(L"����籩", L"�ٻ��޴�Ļ���籩", attackPower * 3, 100);
    }
    
    wstring getTypeDescription() const override {
        return L"�������ר�ң��ó����湥��";
    }
    
    wstring getEntranceQuote() const override {
        return L"׼���ñ�������������";
    }
    
    wstring getVictoryQuote() const override {
        return L"����������³���";
    }
};

// ˮ����С���飨KOF���
class WaterSniper : public Character {
public:
    WaterSniper() : Character(L"ˮ֮�ѻ���", 1000, 100) {
        // ��ʼ����ʽ
        moves[L"ˮ��"] = new NormalAttack(L"ˮ��", L"�����ѹˮ��", attackPower);
        moves[L"ˮ��"] = new NormalAttack(L"ˮ��", L"��������ˮ��", attackPower * 1.1);
        moves[L"ˮ����"] = new SpecialMove(L"ˮ����", L"�þ޴��ˮ����ס����", attackPower * 1.8, 30);
        moves[L"��Х�籩"] = new SuperMove(L"��Х�籩", L"�ٻ��޴�ĺ�Х��û����", attackPower * 3.5, 100);
    }
    
    wstring getTypeDescription() const override {
        return L"Զ�̹���ר�ң��ó����ƺͷ�Χ�˺�";
    }
    
    wstring getEntranceQuote() const override {
        return L"��ˮ�в����ɣ�";
    }
    
    wstring getVictoryQuote() const override {
        return L"��ķ�������ˮ���뺣��";
    }
};

// ������С���飨KOF���
class ThunderWarrior : public Character {
public:
    ThunderWarrior() : Character(L"����սʿ", 900, 120) {
        // ��ʼ����ʽ
        moves[L"����ȭ"] = new NormalAttack(L"����ȭ", L"��������Ŀ���ȭ��", attackPower);
        moves[L"�׹���"] = new NormalAttack(L"�׹���", L"���������ǿ���߻�", attackPower * 1.2);
        moves[L"�׹�����"] = new SpecialMove(L"�׹�����", L"���������繥��", attackPower * 2, 30);
        moves[L"������"] = new SuperMove(L"������", L"�ٻ�����֮�����л����Դ��", attackPower * 4, 100);
    }
    
    wstring getTypeDescription() const override {
        return L"�ٶ���սʿ���ó������ͱ���";
    }
    
    wstring getEntranceQuote() const override {
        return L"�����׵�������ɣ�";
    }
    
    wstring getVictoryQuote() const override {
        return L"�׵粻�����λ���ͬһ���ط�...���һᣡ";
    }
};

// ����BOSS��ɫ
class FrostQueen : public Character {
public:
    FrostQueen() : Character(L"��˪", 1400, 140) {
        // ��ʼ������̨��
        taunts.clear();  // ����������������Ҫ��
        taunts.push_back(L"���ǽ�����Զ���⣡");
        taunts.push_back(L"���ܾ�����ȵĿ־�ɣ�");
        taunts.push_back(L"�ڱ�������ڰɣ�");
        taunts.push_back(L"���佫�������ǵ���꣡");
        taunts.push_back(L"������罫���һƬ��ԭ��");
        
        // ��ʼ����ʽ
        moves[L"���⴩��"] = new NormalAttack(L"���⴩��", L"�ӵ���̳������ı���", attackPower);
        moves[L"��˪���"] = new NormalAttack(L"��˪���", L"�ͷź�˪�������г��", attackPower * 1.3);
        moves[L"����ѩ"] = new SpecialMove(L"����ѩ", L"�ٻ����ҵı���ѩ��������", attackPower * 2.5, 40);
        moves[L"�������"] = new SuperMove(L"�������", L"����Χ�¶Ƚ���������ȣ���ɻ������˺�", attackPower * 5, 120);
    }
    
    wstring getTypeDescription() const override {
        return L"������";
    }
    
    wstring getEntranceQuote() const override {
        return L"�ҽ�����Щ����....ͳ�����磡";
    }
    
    wstring getVictoryQuote() const override {
        return L"���ڣ�֪���ҵ���������";
    }
};

// ս��������
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
        // ��ɾ����ɫ����Ϊ������GameManager����
    }
    
    // ��ʾս������
    void displayBattleScreen() {
        clearScreen();
        
        wcout << L"=== �� " << round << L" �غ� ===" << endl;
        wcout << L"[" << player->getName() << L"] VS [" << opponent->getName() << L"]" << endl;
        wcout << L"----------------------------------------" << endl;
        
        // ��ʾ���״̬
        wcout << L"��: ";
        player->displayStatus();
        
        // ��ʾ����״̬
        wcout << L"\n����: ";
        opponent->displayStatus();
        
        wcout << L"----------------------------------------" << endl;
    }
    
    // ��һغ�
    void playerTurn() {
        displayBattleScreen();
        wcout << L"\n--- ��Ļغ� ---" << endl;
        
        player->unblock();  // �غϿ�ʼȡ������
        
        while (true) {
            wcout << L"\nѡ���ж�:" << endl;
            wcout << L"1. �鿴��ʽ�б�" << endl;
            wcout << L"2. ʹ����ʽ" << endl;
            wcout << L"3. ����" << endl;
            wcout << L"4. �������" << endl;
            
            int choice;
            do {
                wcout << L"����ѡ�� (1-4): ";
                wcin >> choice;
                wcin.ignore();  // ������뻺����
            } while (choice < 1 || choice > 4);
            
            switch (choice) {
                case 1: {  // �鿴��ʽ�б�
                    player->displayMoves();
                    wcout << L"\n��Enter����..." << endl;
                    wcin.ignore();
                    wcin.get();
                    break;
                }
                
                case 2: {  // ʹ����ʽ
                    wcout << L"\n������ʽ����: ";
                    wstring moveName;
                    getline(wcin, moveName);
                    
                    Move* move = player->getMove(moveName);
                    if (move) {
                        int damage = move->execute(player, opponent);
                        if (damage > 0) {
                            opponent->takeDamage(damage);
                            
                            // �ɹ�ʹ����ʽ����۶�������
                            int energyGain = max(1, move->getEnergyCost() / 3);
                            player->gainEnergy(energyGain);
                        }
                        return;
                    } else {
                        wcout << L"��Ч����ʽ���ƣ�" << endl;
                        delay(1000);
                    }
                    break;
                }
                
                case 3: {  // ����
                    player->block();
                    wcout << L"������˷���״̬��" << endl;
                    delay(1500);
                    return;
                }
                
                case 4: {  // ����
                    wcout << player->getName() << L": " << player->getRandomTaunt() << endl;
                    delay(1000);
                    
                    // ���ֿ��ܱ���ŭ�����������ʽ���
                    wcout << opponent->getName() << L" ����ŭ�ˣ�" << endl;
                    delay(1000);
                    break;
                }
            }
        }
    }
    
    // ���ֻغ�
    void opponentTurn() {
        displayBattleScreen();
        wcout << L"\n--- ���ֻغ� ---" << endl;
        delay(1000);
        
        opponent->unblock();  // �غϿ�ʼȡ������
        
        // ����AI����
        vector<wstring> availableMoves = opponent->getMoveNames();
        vector<wstring> validMoves;
        
        // ɸѡ�������㹻����ʽ
        for (const auto& moveName : availableMoves) {
            Move* move = opponent->getMove(moveName);
            if (move && opponent->getEnergy() >= move->getEnergyCost()) {
                validMoves.push_back(moveName);
            }
        }
        
        // ���û���㹻��������ʽ��ֻ��ʹ����ͨ����
        if (validMoves.empty()) {
            for (const auto& moveName : availableMoves) {
                Move* move = opponent->getMove(moveName);
                if (move && move->getEnergyCost() == 0) {
                    validMoves.push_back(moveName);
                }
            }
        }
        
        if (validMoves.empty()) {
            wcout << opponent->getName() << L" �����������޷��ж���" << endl;
            return;
        }
        
        // ���ݶ�������ֵ��������
        bool isDesperate = opponent->getHealth() < opponent->getMaxHealth() / 3;
        
        // ���ѡ��һ����ʽ������ʱ��������ʹ�ø��˺���ʽ
        wstring chosenMove;
        if (isDesperate && opponent->getEnergy() >= 80) {
            // ����ʱ����ʹ�ó���ɱ��
            for (const auto& moveName : validMoves) {
                Move* move = opponent->getMove(moveName);
                if (move->getEnergyCost() >= 80) {
                    chosenMove = moveName;
                    break;
                }
            }
        }
        
        if (chosenMove.empty()) {
            // �������ѡ��
            chosenMove = validMoves[rand() % validMoves.size()];
        }
        
        Move* move = opponent->getMove(chosenMove);
        
        wcout << opponent->getName() << L" ׼��ʹ�� " << chosenMove << L"��" << endl;
        delay(1500);
        
        int damage = move->execute(opponent, player);
        if (damage > 0) {
            player->takeDamage(damage);
            
            // �ɹ�ʹ����ʽ����۶�������
            int energyGain = max(1, move->getEnergyCost() / 3);
            opponent->gainEnergy(energyGain);
        }
        
        delay(2000);
    }
    
    // ���ս���Ƿ����
    bool checkBattleOver() {
        if (!player->isAlive()) {
            displayBattleScreen();
            wcout << L"\n=== ս������ ===" << endl;
            wcout << opponent->getName() << L" ��ʤ��" << endl;
            wcout << opponent->getVictoryQuote() << endl;
            battleOver = true;
            return true;
        }
        
        if (!opponent->isAlive()) {
            displayBattleScreen();
            wcout << L"\n=== ս������ ===" << endl;
            wcout << player->getName() << L" ��ʤ��" << endl;
            wcout << player->getVictoryQuote() << endl;
            battleOver = true;
            return true;
        }
        
        return false;
    }
    
    // ����һ�غ�ս��
    void fightRound() {
        displayBattleScreen();
        wcout << L"\n=== �غϿ�ʼ ===" << endl;
        delay(2000);
        
        // ս�����̣��ϸ�غ��ƣ���һ����һ�أ�
        playerTurn();
        if (checkBattleOver()) return;
        
        opponentTurn();
        checkBattleOver();
        
        // �غϽ���
        if (!battleOver) {
            round++;
            wcout << L"\n=== �غϽ��� ===" << endl;
            wcout << L"��Enter������һ�غ�..." << endl;
            wcin.ignore();
            wcin.get();
        }
    }
    
    // ս����ѭ��
    bool startBattle() {
        // ս������
        displayBattleScreen();
        wcout << L"\n=== ս����ʼ ===" << endl;
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
        
        // ս��ѭ��
        while (!battleOver) {
            fightRound();
        }
        
        // ����ս�������true��ʾ���ʤ����false��ʾʧ�ܣ�
        return player->isAlive();
    }
};

// ���������
class StoryManager {
public:
    // �������ؾ���
    static void triggerHiddenStory(Character* player) {
        clearScreen();
        
        wcout << L"" << endl;
	}
};