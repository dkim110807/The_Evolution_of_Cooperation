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

    virtual void description() = 0;

    virtual Choice::ChoiceRef choose() = 0;

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

    void description() override {
        std::cout << "Tit for Tat :                                                        \n"
                     "    1. 처음에는 협력한다.                                               \n"
                     "    2. 이후에는 상대방이 바로 직전에 했던 판단(행동)을 똑같이 따라해 되갚아 준다.\n";
    }

    Choice::ChoiceRef choose() override {
        return choices.empty() ? Choice::C : choices.back();
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

    void description() override {
        std::cout << "Random (50%, 50%) : 50%의 확률로 배반하고, 50%의 확률로 협력한다.\n";
    }

    Choice::ChoiceRef choose() override {
        return generator() <= 50 ? Choice::C : Choice::D;
    }
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

    void description() override {
        std::cout << "Random (90%, 10%) : 90%의 확률로 배반하고, 10%의 확률로 협력한다.\n";
    }

    Choice::ChoiceRef choose() override {
        return generator() <= 10 ? Choice::C : Choice::D;
    }
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

    void description() override {
        std::cout << "Random (10%, 90%) : 10%의 확률로 배반하고, 90%의 확률로 협력한다.\n";
    }

    Choice::ChoiceRef choose() override {
        return generator() <= 90 ? Choice::C : Choice::D;
    }
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

    void description() override {
        std::cout << "Tit for 2 Tat :                                                      \n"
                     "    1. 처음에는 협력한다.                                               \n"
                     "    2. 상대방이 연속으로 두 번 배반했다면 배반하고, 이외의 모든 경우는 협력한다. \n";
    }

    Choice::ChoiceRef choose() override {
        // 첫번째와 두번째는 협력한다.
        if (choices.size() <= 1) return Choice::C;
        auto k = choices.size();
        if (choices[k - 1] == choices[k - 2] && choices[k - 1] == Choice::D) return Choice::D;
        return Choice::C;
    }
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

    void description() override {
        std::cout << "Friedman :                                                          \n"
                     "    1. 첫게임은 협력한다.                                              \n"
                     "    2. 이후에는 상대가 협력하면 협력하고, 배반하면 이후 모든 게임에서 배반한다. \n";
    }

    Choice::ChoiceRef choose() override {
        if (choices.empty()) return Choice::C;
        if (choices.back() == Choice::D) betrayed = true;
        return betrayed ? Choice::D : Choice::C;
    }
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

    void description() override {
        std::cout << "All D : 상대의 선택과 관계 없이 항상 배반한다.\n";
    }

    Choice::ChoiceRef choose() override {
        return Choice::D;
    }
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

    void description() override {
        std::cout << "All C : 상대의 선택과 관계 없이 항상 협력한다.\n";
    }

    Choice::ChoiceRef choose() override {
        return Choice::C;
    }
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

    void description() override {
        std::cout << "Tester : \n"
                     "    1. 첫번째와 두번째 게임에서 무조건 배반한다.\n"
                     "    2. 다음 게임에서 상대가 배반할 경우 팃포택으로 가고, 상대가 협력할 경우 3, 4번째 게임에서는 협력을 하고 이후 "
                     "부터 협력과 배반을 번갈아 한다.\n";
    }

    Choice::ChoiceRef choose() override {
        if (choices.size() <= 1) return Choice::D;
        if (choices.size() == 2 && choices.back() == Choice::D) tit = true;
        if (tit && choices.size() == 2) return Choice::C;
        else if (tit) return choices.back();
        else if (choices.size() <= 3) return Choice::C;
        else return choices.size() % 2 ? Choice::D : Choice::C;
    }
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

    void description() override {
        std::cout << "Tit for Tat :                                                        \n"
                     "    1. 처음에는 협력한다.                                               \n"
                     "    2. 이후에는 상대방이 바로 직전에 했던 판단(행동)을 똑같이 따라해 되갚아 주는데, 상대가 협력한 다음 10%의 확률로 배반을 한다.\n";
    }

    Choice::ChoiceRef choose() override {
        if (choices.empty()) return Choice::C;
        if (choices.back() == Choice::C) {
            return generator() <= 10 ? Choice::D : Choice::C;
        }
        return Choice::D;
    }
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

    void description() override {
        std::cout << "Alternative : 처음에는 협력을 하고, 이후에는 배반과 협력을 한다.\n";
    }

    Choice::ChoiceRef choose() override {
        if (choices.size() % 2 == 0) return Choice::C;
        return Choice::D;
    }
};

int rewards[2][2] = {
        {Reward::P, Reward::T},
        {Reward::S, Reward::R}
};

std::pair<int, int> game(Strategy *A, Strategy *B) {
    int score[] = {0, 0};
    for (int i = 0; i < 50; i++) {
        auto a = A->choose(), b = B->choose();

        std::cout << "A : " << a << ", B : " << b << "\n";

        score[0] += rewards[a][b], score[1] += rewards[b][a];

        A->add_choice(b), B->add_choice(a);
    }

    std::cout << "Score : " << score[0] << " " << score[1] << "\n";
    if (score[0] > score[1]) {
        std::cout << "A wins : ";
        A->description();
    } else if (score[0] == score[1]) {
        std::cout << "Draw";
    } else {
        std::cout << "B wins : ";
        B->description();
    }
    return {score[0], score[1]};
}

int main() {
    game(new Friedman(), new Joss());
}
