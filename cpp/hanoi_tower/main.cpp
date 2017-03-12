#include <tuple>
#include <vector>
#include <iostream>


void move_tower(int nthPlate, int fromIndex, int toIndex, int remainingIndex)
{
    if (1 == nthPlate) { // if top plate,
        std::cout << "plate-" << nthPlate << ", (" << fromIndex << " => " << toIndex << ")" << std::endl;
        return;
    }
    move_tower(nthPlate - 1, fromIndex, remainingIndex, toIndex);
    std::cout << "plate-" << nthPlate << ", (" << fromIndex << " => " << toIndex << ")" << std::endl;
    move_tower(nthPlate - 1, remainingIndex, toIndex, fromIndex);
}


struct TowerMovementSequenceHolder
{
    using tower_movement = std::tuple<int, int, int>;

    std::vector<tower_movement> towerMovementSequence_;

    void generate(int nthPlate, int fromIndex, int toIndex, int remainingIndex)
    {
        using std::make_tuple;
        if (1 == nthPlate) { // if top plate,
            towerMovementSequence_.push_back(make_tuple(nthPlate, fromIndex, toIndex));
            return;
        }
        generate(nthPlate - 1, fromIndex, remainingIndex, toIndex);
        towerMovementSequence_.push_back(make_tuple(nthPlate, fromIndex, toIndex));
        generate(nthPlate - 1, remainingIndex, toIndex, fromIndex);
    }
};


template <int i>
using int_c_t = std::integral_constant<int, i>;

template <typename NthPlate, typename FromIndex, typename ToIndex>
using plate_movement_t = std::tuple<NthPlate, FromIndex, ToIndex>;

template <typename... Sequence>
struct TowerMovementSequence
{ };

template <typename TowerMovementSequence, typename... Movement>
struct JoinTowerMovementSequence;

template <typename TowerMovementSequence, typename Head, typename... Tail>
struct JoinTowerMovementSequence<TowerMovementSequence, Head, Tail...>
{
    using type = typename JoinTowerMovementSequence<
                                typename JoinTowerMovementSequence<TowerMovementSequence, Head>::type,
                                Tail...
                            >::type;
};

template <typename... Sequence, typename NthPlate, typename FromIndex, typename ToIndex>
struct JoinTowerMovementSequence
        <
            TowerMovementSequence<Sequence...>,
            plate_movement_t<NthPlate, FromIndex, ToIndex>
        >
{
    using type = TowerMovementSequence<Sequence..., plate_movement_t<NthPlate, FromIndex, ToIndex>>;
};

template <typename... Sequence1, typename... Sequence2>
struct JoinTowerMovementSequence
        <
            TowerMovementSequence<Sequence1...>,
            TowerMovementSequence<Sequence2...>
        >
{
    using type = TowerMovementSequence<Sequence1..., Sequence2...>;
};

template <typename NthPlateIndex, typename FromIndex, typename ToIndex, typename RemainingIndex>
struct MoveTower
{
    using upper_plate_movement_sequence_1_t = typename MoveTower<
                                                            int_c_t<NthPlateIndex::value - 1>,
                                                            FromIndex,
                                                            RemainingIndex,
                                                            ToIndex
                                                        >::type;
    using current_plate_movement_t = plate_movement_t<
                                            NthPlateIndex,
                                            FromIndex,
                                            ToIndex
                                        >;
    using upper_plate_movement_sequence_2_t = typename MoveTower<
                                                            int_c_t<NthPlateIndex::value - 1>,
                                                            RemainingIndex,
                                                            ToIndex,
                                                            FromIndex
                                                        >::type;
    using type = typename JoinTowerMovementSequence<
                                upper_plate_movement_sequence_1_t,
                                current_plate_movement_t,
                                upper_plate_movement_sequence_2_t
                            >::type;
};

template <typename FromIndex, typename ToIndex, typename RemainingIndex>
struct MoveTower<int_c_t<1>, FromIndex, ToIndex, RemainingIndex>
{
    using type = TowerMovementSequence<plate_movement_t<int_c_t<1>, FromIndex, ToIndex>>;
};

template <typename PlateMovement>
void PrintTowerMovementSequence(TowerMovementSequence<PlateMovement>)
{
    std::cout << "plate-" << std::tuple_element_t<0, PlateMovement>::value << ","
                << " (" << std::tuple_element_t<1, PlateMovement>::value
                << " => " << std::tuple_element_t<2, PlateMovement>::value << ")"
                << std::endl;
}

template <typename PlateMovement, typename Head, typename... Tail>
void PrintTowerMovementSequence(TowerMovementSequence<PlateMovement, Head, Tail...>)
{
    std::cout << "plate-" << std::tuple_element_t<0, PlateMovement>::value << ","
                << " (" << std::tuple_element_t<1, PlateMovement>::value
                << " => " << std::tuple_element_t<2, PlateMovement>::value << ")"
                << std::endl;
    PrintTowerMovementSequence(TowerMovementSequence<Head, Tail...>());
}


int main() {
    constexpr int towerHeight = 5;

    // runtime version 1
    move_tower(towerHeight, 0, 2, 1);

    // runtime version 2
    using std::cout;
    using std::endl;
    using std::get;

    cout << "\n--- runtime version 2" << endl;

    TowerMovementSequenceHolder seqHolder;
    seqHolder.generate(towerHeight, 0, 2, 1);
    for (auto & seq : seqHolder.towerMovementSequence_) {
        cout << "plate-" << get<0>(seq) << ", (" << get<1>(seq) << " => " << get<2>(seq) << ")" << endl;
    }

    // compile-time version
    using std::cout;
    using std::endl;
    using std::get;

    cout << "\n--- compile-time version" << endl;

    using tower_movement_sequence_t = typename MoveTower<
                                                    int_c_t<towerHeight>,
                                                    int_c_t<0>,
                                                    int_c_t<2>,
                                                    int_c_t<1>
                                                >::type;
    PrintTowerMovementSequence(tower_movement_sequence_t());

    return 0;
}

