#include <bits/stdc++.h>
#include "random.h"

/**
 * <b> 협력의 진화 - 로버트 액설로드 </b>
 *
 * <hr>
 * <b> Credit </b>
 * <br><a href="http://www-personal.umich.edu/~axe/research/Axelrod%20and%20Hamilton%20EC%201981.pdf">http://www-personal.umich.edu/~axe/research/Axelrod%20and%20Hamilton%20EC%201981.pdf</a>
 * <br> The Evolution of Cooperation - Robert Axelrod </a>
 * @author dkim110807
 */

/**
 * <b> 죄수의 딜레마 - 보상 </b>
 *
 * <hr>
 *
 * <li> T : 배반에 대한 보상(배반 - 협력) </li>
 * <li> R : 상호 협력에 대한 보상 </li>
 * <li> P : 상호 배반에 대한 보상 </li>
 * <li> S : 협력에 대한 보상(배반 - 협력) </li>
 *
 * <hr>
 * <br> 보상은 꼭 비교가능한 변수가 아니여도 되고, 아래 조건을 만족해야만 한다.
 * <br> → T > R > P > S and R > (T + S) / 2
 * <br>
 * <br> 여기서는 T = 5, R = 3, P = 1, S = 0으로 한다.
 *
 * @author dkim110807
 */
namespace Reward {
    typedef int RewardRef;

    /**
     * 배반에 대한 보상 (Defection - Cooperation)
     */
    static const RewardRef T = 5;
    /**
     * 상호 협력에 대한 보상 (Cooperation - Cooperation)
     */
    static const RewardRef R = 3;
    /**
     * 상호 배반에 대한 보상 (Defection - Defection)
     */
    static const RewardRef P = 1;
    /**
     * 협력에 대한 보상 (Cooperation - Defection)
     */
    static const RewardRef S = 0;
}

/**
 * <b> 죄수의 딜레마 - 선택 </b>
 *
 * <hr>
 *
 * <li> C(Cooperation) : 협력 </li>
 * <li> D(Defection)   : 배반 </li>
 *
 * <hr>
 *
 * @author dkim110807
 */
namespace Choice {
    typedef int ChoiceRef;

    /**
     * 협력 (Cooperation)
     */
    static const ChoiceRef C = 1;
    /**
     * 배반 (Defection)
     */
    static const ChoiceRef D = 0;
}

class Strategy {
protected:
    // 상대방이 선택한 선택들 (협력 or 배반)
    std::vector<Choice::ChoiceRef> choices;

public:

    Strategy() = default;

    virtual std::string name() = 0;

    virtual std::string description() = 0;

    virtual Choice::ChoiceRef choose() = 0;

    virtual void clear() = 0;

    void add_choice(Choice::ChoiceRef choice) {
        choices.push_back(choice);
    }
};

/**
 * <b> Tit For Tat </b>
 *
 * <hr>
 * 1. 처음에는 협력한다.
 * <br> 2. 이후에는 상대방이 바로 직전에 했던 판단(행동)을 똑같이 따라해 되갚아 준다.
 * <hr>
 *
 * @author dkim110807
 */
class TitForTat : public Strategy {
public:
    TitForTat() = default;

    std::string name() override {
        return "Tit for Tat";
    }

    std::string description() override {
        return "- 처음에는 협력한다.                                               \n"
               "- 이후에는 상대방이 바로 직전에 했던 판단(행동)을 똑같이 따라해 되갚아 준다.\n";
    }

    Choice::ChoiceRef choose() override {
        return choices.empty() ? Choice::C : choices.back();
    }

    void clear() override {
        choices.clear();
    }
};

/**
 * <b> Random (50%, 50%) </b>
 *
 * <hr>
 * 50%의 확률로 배반하고, 50%의 확률로 협력한다.
 * <hr>
 *
 * @author dkim110807
 */
class Random55 : public Strategy {
private:
    Random<int> generator;

public:
    Random55() {
        generator = Random<int>(1, 100, (unsigned int) time(nullptr));
    };

    std::string name() override {
        return "Random (50%, 50%)";
    }

    std::string description() override {
        return "- 50%의 확률로 배반하고, 50%의 확률로 협력한다.\n";
    }

    Choice::ChoiceRef choose() override {
        return generator() <= 50 ? Choice::C : Choice::D;
    }

    void clear() override {
        choices.clear();
    };
};

/**
 * <b> Random (90%, 10%) </b>
 *
 * <hr>
 * 90%의 확률로 배반하고, 10%의 확률로 협력한다.
 * <hr>
 *
 * @author dkim110807
 */
class Random91 : public Strategy {
private:
    Random<int> generator;

public:
    Random91() {
        generator = Random<int>(1, 100, (unsigned int) time(nullptr));
    };

    std::string name() override {
        return "Random (90%, 10%)";
    }

    std::string description() override {
        return "- 90%의 확률로 배반하고, 10%의 확률로 협력한다.\n";
    }

    Choice::ChoiceRef choose() override {
        return generator() <= 10 ? Choice::C : Choice::D;
    }

    void clear() override {
        choices.clear();
    };
};

/**
 * <b> Random (10%, 90%) </b>
 *
 * <hr>
 * 10%의 확률로 배반하고, 90%의 확률로 협력한다.
 * <hr>
 *
 * @author dkim110807
 */
class Random19 : public Strategy {
private:
    Random<int> generator;

public:
    Random19() {
        generator = Random<int>(1, 100, (unsigned int) time(nullptr));
    };

    std::string name() override {
        return "Random (10%, 90%)";
    }

    std::string description() override {
        return "- 10%의 확률로 배반하고, 90%의 확률로 협력한다.\n";
    }

    Choice::ChoiceRef choose() override {
        return generator() <= 90 ? Choice::C : Choice::D;
    }

    void clear() override {
        choices.clear();
    };
};

/**
 * <b> Tit For 2 Tat </b>
 *
 * <hr>
 * 1. 처음에는 협력한다.
 * <br> 2. 상대방이 연속으로 두 번 배반했다면 배반하고, 이외의 모든 경우는 협력한다.
 * <hr>
 *
 * @author dkim110807
 */
class TitForTwoTat : public Strategy {
public:
    TitForTwoTat() = default;

    std::string name() override {
        return "Tit for 2 Tat";
    }

    std::string description() override {
        return "- 처음에는 협력한다.                                               \n"
               "- 상대방이 연속으로 두 번 배반했다면 배반하고, 이외의 모든 경우는 협력한다. \n";
    }

    Choice::ChoiceRef choose() override {
        // 첫번째와 두번째는 협력한다.
        if (choices.size() <= 1) return Choice::C;
        auto k = choices.size();
        if (choices[k - 1] == choices[k - 2] && choices[k - 1] == Choice::D) return Choice::D;
        return Choice::C;
    }

    void clear() override {
        choices.clear();
    };
};

/**
 * <b> Friedman </b>
 *
 * <hr>
 * 1. 처음에는 협력한다.
 * <br> 2. 이후에는 상대가 협력하면 협력하고, 배반하면 이후 모든 게임에서 배반한다.
 * <hr>
 *
 * @author dkim110807
 */
class Friedman : public Strategy {
private:
    bool betrayed = false;

public:
    Friedman() = default;

    std::string name() override {
        return "Friedman";
    }

    std::string description() override {
        return "- 첫게임은 협력한다.                                              \n"
               "- 이후에는 상대가 협력하면 협력하고, 배반하면 이후 모든 게임에서 배반한다. \n";
    }

    Choice::ChoiceRef choose() override {
        if (choices.empty()) return Choice::C;
        if (choices.back() == Choice::D) betrayed = true;
        return betrayed ? Choice::D : Choice::C;
    }

    void clear() override {
        choices.clear();
        betrayed = false;
    };
};

/**
 * <b> All D </b>
 *
 * <hr>
 * 상대의 선택과 관계 없이 항상 배반한다.
 * <hr>
 *
 * @author dkim110807
 */
class AllD : public Strategy {
public:
    AllD() = default;

    std::string name() override {
        return "All D";
    }

    std::string description() override {
        return "- 상대의 선택과 관계 없이 항상 배반한다.\n";
    }

    Choice::ChoiceRef choose() override {
        return Choice::D;
    }

    void clear() override {
        choices.clear();
    };
};

/**
 * <b> All C </b>
 *
 * <hr>
 * 상대의 선택과 관계 없이 항상 협력한다.
 * <hr>
 *
 * @author dkim110807
 */
class AllC : public Strategy {
public:
    AllC() = default;

    std::string name() override {
        return "All C";
    }

    std::string description() override {
        return "- 상대의 선택과 관계 없이 항상 협력한다.\n";
    }

    Choice::ChoiceRef choose() override {
        return Choice::C;
    }

    void clear() override {
        choices.clear();
    };
};

/**
 * <b> Tester </b>
 *
 * <hr>
 * 1. 첫번째와 두번째 게임에서 무조건 배반한다.
 * <br> 2. 다음 게임에서 상대가 배반할 경우 팃포택으로 가고, 상대가 협력할 경우 3, 4번째 게임에서는 협력을 하고 이후 부터 협력과 배반을 번갈아 한다.
 * <hr>
 *
 * @author dkim110807
 */
class Tester : public Strategy {
private:
    bool tit = false;
public:
    Tester() = default;

    std::string name() override {
        return "Tester";
    }

    std::string description() override {
        return "- 첫번째와 두번째 게임에서 무조건 배반한다.\n"
               "- 다음 게임에서 상대가 배반할 경우 팃포택으로 가고, 상대가 협력할 경우 3, 4번째 게임에서는 협력을 하고 이후 부터 협력과 배반"
               "을 번갈아 한다.\n";
    }

    Choice::ChoiceRef choose() override {
        if (choices.size() <= 1) return Choice::D;
        if (choices.size() == 2 && choices.back() == Choice::D) tit = true;
        if (tit && choices.size() == 2) return Choice::C;
        else if (tit) return choices.back();
        else if (choices.size() <= 3) return Choice::C;
        else return choices.size() % 2 ? Choice::D : Choice::C;
    }

    void clear() override {
        choices.clear();
        tit = false;
    };
};

/**
 * <b> Joss </b>
 *
 * <hr>
 * 1. 처음에는 협력한다.
 * <br> 2. 이후에는 상대방이 바로 직전에 했던 판단(행동)을 똑같이 따라해 되갚아 주는데, 상대가 협력한 다음 10%의 확률로 배반을 한다.
 * <hr>
 *
 * @author dkim110807
 */
class Joss : public Strategy {
private:
    Random<int> generator;

public:
    Joss() {
        generator = Random<int>(1, 100, (unsigned int) time(nullptr));
    }

    std::string name() override {
        return "Joss";
    }

    std::string description() override {
        return "- 처음에는 협력한다.                                               \n"
               "- 이후에는 상대방이 바로 직전에 했던 판단(행동)을 똑같이 따라해 되갚아 주는데, 상대가 협력한 다음 10%의 확률로 배반을 한다.\n";
    }

    Choice::ChoiceRef choose() override {
        if (choices.empty()) return Choice::C;
        if (choices.back() == Choice::C) {
            return generator() <= 10 ? Choice::D : Choice::C;
        }
        return Choice::D;
    }

    void clear() override {
        choices.clear();
    };
};

/**
 * <b> Alternative </b>
 *
 * <hr>
 * 처음에는 협력을 하고, 이후에는 배반과 협력을 교대로 한다.
 * <hr>
 *
 * @author dkim110807
 */
class Alternative : public Strategy {
public:
    Alternative() = default;

    std::string name() override {
        return "Alternative";
    }

    std::string description() override {
        return "- 처음에는 협력을 하고, 이후에는 배반과 협력을 한다.\n";
    }

    Choice::ChoiceRef choose() override {
        if (choices.size() % 2 == 0) return Choice::C;
        return Choice::D;
    }

    void clear() override {
        choices.clear();
    };
};

/**
 * <b> Pavlov </b>
 *
 * <hr>
 * 1. 처음에는 협력을 한다.
 * <br> 2. 이후에는 이전에 상대방과 내가 같은 선택을 했으면 협력, 아니라면 배반을 한다.
 * <hr>
 *
 * @author dkim110807
 */
class Pavlov : public Strategy {
private:
    // 내가 선택한 선택들
    std::vector<Choice::ChoiceRef> mchoices;

public:
    Pavlov() = default;

    std::string name() override {
        return "Pavlov";
    }

    std::string description() override {
        return "- 처음에는 협력을 한다.                                              \n"
               "- 이후에는 이전에 상대방과 내가 같은 선택을 했으면 협력, 아니라면 배반을 한다.\n";
    }

    Choice::ChoiceRef choose() override {
        if (mchoices.empty()) mchoices.push_back(Choice::C);
        else mchoices.push_back(mchoices.back() == choices.back() ? Choice::C : Choice::D);
        return mchoices.back();
    }

    void clear() override {
        choices.clear();
        mchoices.clear();
    };
};

/**
 * <b> Mistrust </b>
 *
 * <hr>
 * 1. 처음에는 배반을 한다.
 * <br> 2. 이후에는 상대방이 전에 했던 행동을 따라한다.
 * <hr>
 *
 * @author dkim110807
 */
class Mistrust : public Strategy {
public:
    Mistrust() = default;

    std::string name() override {
        return "Mistrust";
    }

    std::string description() override {
        return "- 처음에는 배반한다.     \n"
               "- 이후에는 상대방이 전에 했던 행동을 따라한다. \n";
    }

    Choice::ChoiceRef choose() override {
        if (choices.empty()) return Choice::D;
        return choices.back();
    }

    void clear() override {
        choices.clear();
    };
};

/**
 * <b> Soft Major </b>
 *
 * <hr>
 * 1. 처음에는 협력을 한다.
 * <br> 2. 이후에는 상대방이 배신한 횟수가 더 많으면 배반하고, 아니라면 협력한다.
 * <hr>
 *
 * @author dkim110807
 */
class SoftMajor : public Strategy {
private:
    int betray = 0;

public:
    SoftMajor() = default;

    std::string name() override {
        return "Soft Major";
    }

    std::string description() override {
        return "- 처음에는 협력한다. \n"
               "- 이후에는 상대방이 배신한 횟수가 더 많으면 배반하고, 아니라면 협력한다.\n";
    }

    Choice::ChoiceRef choose() override {
        if (choices.empty()) return Choice::C;
        betray += choices.back() == Choice::D;
        if (choices.size() / 2 < betray) return Choice::D;
        return Choice::C;
    }

    void clear() override {
        choices.clear();
        betray = 0;
    };
};

/**
 * <b> Hard Forgiver </b>
 *
 * <hr>
 * 1. 처음 두번은 협력한다.
 * <br> 2. 3번째 부터 2턴 이후 배반이 있다면 배반, 연속 두 번 협력하면 다시 협력한다.
 * <br> 3. 이후 또 배반하면, 3턴 연속 협력이어야 협력한다.
 * <br> 4. 이후 또 배반하면, 계속 배반한다.
 * <hr>
 *
 * @author dkim110807
 */
class HardForgiver : public Strategy {
private:
    bool forgive() {
        int betray = 0;
        for (auto &i: choices) betray += i == Choice::D;
        if (betray == 0) return true;
        if (betray >= 3) return false;
        for (int i = (int) choices.size() - 1; i >= choices.size() - betray; i--)
            if (choices[i] == Choice::D)
                return false;
        return true;
    }

public:
    HardForgiver() = default;

    std::string name() override {
        return "Hard Forgiver";
    }

    std::string description() override {
        return "- 처음 두번은 협력한다. \n"
               "- 3번째 부터 2턴 이후 배반이 있다면 배반, 연속 두 번 협력하면 다시 협력한다. \n"
               "- 이후 또 배반하면, 3턴 연속 협력이어야 협력한다. \n"
               "- 이후 또 배반하면, 계속 배반한다.\n";
    }

    Choice::ChoiceRef choose() override {
        if (choices.size() <= 1 || forgive()) return Choice::C;
        return Choice::D;
    }

    void clear() override {
        choices.clear();
    };
};

/**
 * <b> Prober </b>
 *
 * <hr>
 * 1. 협력, 배반, 배반으로 시작한다.
 * <br> 2. 2~3턴에서 계속 상대가 협력시 계속 배반하고, 아니라면 Tit for Tat으로 나머지 턴을 플레이한다.
 * <hr>
 *
 * @author dkim110807
 */
class Prober : public Strategy {
public:
    Prober() = default;

    std::string name() override {
        return "Prober";
    }

    std::string description() override {
        return "- 협력, 배반, 배반으로 시작한다. \n"
               "- 2~3턴에서 계속 상대가 협력시 계속 배반하고, 아니라면 Tit for Tat으로 나머지 턴을 플레이한다.\n";
    }

    Choice::ChoiceRef choose() override {
        if (choices.empty()) return Choice::C;
        if (choices.size() < 3) return Choice::D;
        if (choices[1] == choices[2] && choices[1] == Choice::C) return Choice::D;
        return choices.back();
    }

    void clear() override {
        choices.clear();
    };
};

/**
 * <b> Per Nasty </b>
 *
 * <hr>
 * 1. 배반, 배반, 협력을 반복한다.
 * <hr>
 *
 * @author dkim110807
 */
class PerNasty : public Strategy {
public:
    PerNasty() = default;

    std::string name() override {
        return "Per Nasty";
    }

    std::string description() override {
        return "- 배반, 배반, 협력을 반복한다. \n";
    }

    Choice::ChoiceRef choose() override {
        if (choices.size() % 3 == 2) return Choice::C;
        return Choice::D;
    }

    void clear() override {
        choices.clear();
    };
};

/**
 * <b> Downing </b>
 *
 * <hr>
 * 1. 처음에는 배반을 한다.
 * <br> 2. 이후에는 (상대가 배반한 횟수) / (총 게임 횟수)의 확률로 배반한다.
 * <hr>
 *
 * @author dkim110807
 */
class Downing : public Strategy {
private:
    Random<int> generator;
    int p = 500;
    int betray = 0;

public:
    Downing() {
        generator = Random<int>(1, 1000, (unsigned int) time(nullptr));
    }

    std::string name() override {
        return "Downing";
    }

    std::string description() override {
        return "- 처음에는 배반을 한다. \n"
               "- 이후에는 (상대가 배반한 횟수) / (총 게임 횟수)의 확률로 배반한다.\n";
    }

    Choice::ChoiceRef choose() override {
        if (!choices.empty()) {
            betray += choices.back() == Choice::D;
            p = 1000 * betray / (int) choices.size();
        }
        // 확률이 같은 경우
        if (p == 500) return Choice::D;
        if (generator() >= p) return Choice::C;
        return Choice::D;
    }

    void clear() override {
        choices.clear();
        p = 500, betray = 0;
    };
};

/**
 * <b> Modified Downing </b>
 *
 * <hr>
 * 1. 처음에는 협력을 한다.
 * <br> 2. 이후에는 (상대가 배반한 횟수) / (총 게임 횟수)의 확률로 배반한다.
 * <hr>
 *
 * @author dkim110807
 */
class ModifiedDowning : public Strategy {
private:
    Random<int> generator;
    int p = 500;
    int betray = 0;

public:
    ModifiedDowning() {
        generator = Random<int>(1, 1000, (unsigned int) time(nullptr));
    }

    std::string name() override {
        return "Modified Downing";
    }

    std::string description() override {
        return "- 처음에는 협력을 한다. \n"
               "- 이후에는 (상대가 배반한 횟수) / (총 게임 횟수)의 확률로 배반한다.\n";
    }

    Choice::ChoiceRef choose() override {
        if (!choices.empty()) {
            betray += choices.back() == Choice::D;
            p = 1000 * betray / (int) choices.size();
        }
        // 확률이 같은 경우
        if (p == 500) return Choice::C;
        if (generator() >= p) return Choice::C;
        return Choice::D;
    }

    void clear() override {
        choices.clear();
        p = 500, betray = 0;
    };
};

Reward::RewardRef rewards[2][2] = {
        {Reward::P, Reward::T},
        {Reward::S, Reward::R}
};

std::tuple<int, int> game(Strategy *A, Strategy *B, int iter) {
    int score[] = {0, 0};

    A->clear(), B->clear();
    std::cout << "Player A : " << A->name() << ", Player B : " << B->name() << "\n";

    auto print = [&](int x) {
        if (x == 0) return "D";
        return "C";
    };

    for (int i = 0; i < iter; i++) {
        Choice::ChoiceRef a = A->choose(), b = B->choose();

        if (iter <= 50) std::cout << "A : " << print(a) << ", B : " << print(b) << "\n";

        score[0] += rewards[a][b], score[1] += rewards[b][a];

        A->add_choice(b), B->add_choice(a);
    }

    std::cout << "A : " << score[0] << ", B : " << score[1] << "\n";
    std::cout << "------------------------------------------------\n";

    return {score[0], score[1]};
}

void round_robin(const std::vector<Strategy *> &players, int iter) {
    std::ifstream data("simulate/robin/data.txt");
    int num = 0;
    while (!data.eof()) data >> num;
    std::cout << "Simulation No." << num;
    std::ofstream("simulate/robin/data.txt") << num + 1;

    std::ofstream file("simulate/robin/" + std::to_string(num) + ".txt");
    freopen(("simulate/robin/" + std::to_string(num) + ".txt").c_str(), "w", stdout);

    std::cout << "Number of rounds : " << iter << "\n\n";

    std::vector<Strategy *> list = players;
    int n = (int) list.size();
    for (auto &player: list) {
        std::cout << player->name() << "\n" << player->description() << "\n";
    }

    std::map<Strategy *, std::pair<int, int>> score;

    for (int t = 0; t < n - 1; t++) {
        std::cout << "=======================================================================\n";
        std::cout << "Left Strategy : " << list.size() << "\n";
        for (auto &x: list) std::cout << x->name() << " ";
        std::cout << "\n\n";

        std::vector<std::pair<int, Strategy *>> scores(list.size());
        for (int i = 0; i < list.size(); i++) scores[i] = {0, list[i]};

        for (int i = 0; i < list.size(); i++) {
            for (int j = i + 1; j < list.size(); j++) {
                auto[x, y] = game(list[i], list[j], iter);
                scores[i].first += x, scores[j].first += y;
            }
        }

        for (int i = 0; i < list.size(); i++) scores[i].first /= int(list.size() - 1);

        std::sort(scores.begin(), scores.end(), [&](const std::pair<int, Strategy *> &a, std::pair<int, Strategy *> b) {
            return a.first > b.first;
        });

        for (int i = 0; i < list.size(); i++) {
            std::cout << i + 1 << ". " << scores[i].second->name() << " " << scores[i].first << "\n";
        }

        if (scores.back().first != scores.front().first) {
            for (int i = 0; i < list.size(); i++) score[scores[i].second].second += scores[i].first;
            Strategy *x = scores.back().second;
            score[x].first = (int) list.size();
            score[x].second /= int(n - list.size() + 1);
            scores.pop_back();
            int y = (int) list.size();
            for (int i = 0; i < y; i++) {
                if (list[i]->name() == x->name()) continue;
                list.push_back(list[i]);
            }
            list.erase(list.begin(), list.begin() + y);
        } else {
            for (int i = 0; i < list.size(); i++) score[scores[i].second].second += scores[i].first;
            if (t == n - 2)
                for (int i = 0; i < list.size(); i++)
                    score[scores[i].second].second /= (n - 1), score[scores[i].second].first = i + 1;
        }
    }

    std::cout << "=======================================================================\n\n\n"
                 "-------------------------------Standings-------------------------------\n";

    std::vector<std::pair<int, Strategy *>> standing(n);
    for (auto &i: players) standing[score[i].first - 1] = {score[i].second, i};

    std::sort(standing.begin(), standing.end(), [&](const std::pair<int, Strategy *> &a, std::pair<int, Strategy *> b) {
        return a.first > b.first;
    });

    for (int i = 0; i < n; i++) {
        std::cout << i + 1 << ". " << standing[i].second->name() << " " << standing[i].first << "\n";
    }
}

int main() {
    Strategy *strategies[] = {new TitForTat(), new Random55(), new Random91(), new Random19(), new TitForTwoTat(),
                              new Friedman(), new AllD(), new AllC(), new Tester(), new Joss(), new Alternative(),
                              new Pavlov(), new Mistrust(), new SoftMajor(), new HardForgiver(), new Prober(),
                              new PerNasty(), new Downing(), new ModifiedDowning()};

    std::vector<Strategy *> list;
    for (auto &x: strategies) list.push_back(x);

    int iter;
    std::cin >> iter;
    round_robin(list, iter);
}
