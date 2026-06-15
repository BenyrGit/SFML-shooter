#pragma once

namespace Category
{
    // on utilise des masques de bits, pour qu'un commande puisse cibler plusieurs catégories
    enum Type
    {
        None = 0,
        Scene = 1 << 0,
        PlayerAircraft = 1 << 1,
        AlliedAircraft = 1 << 2,
        EnemyAircraft = 1 << 3
    };
}