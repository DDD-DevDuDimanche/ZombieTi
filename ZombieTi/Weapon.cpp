#include "pch.h"
#include "Weapon.h"

Weapon Weapon::WeaponData[16] = {
	Weapon("Révolver", 5),
	Weapon("Desert Eagle", 7),
	Weapon("Uzi", 9),
	Weapon("MP5", 12),
	Weapon("MP7", 15),
	Weapon("MTAR", 19),
	Weapon("AK-47", 24),
	Weapon("SMR", 30),
	Weapon("Peacekeeper", 38),
	Weapon("Ballista", 48),
	Weapon("XPR-50", 60),
	Weapon("RPG", 75),
	Weapon("Lance-Flamme", 94),
	Weapon("Pistolet Laser", 118),
	Weapon("Fusil Plasma", 148),
	Weapon("Canon à particule", 185)
};

Weapon::Weapon(std::string name, int damage)
{
	_name = name;
	_damage = damage;
}

std::string Weapon::getName()
{
	return _name;
}

int Weapon::getDamage()
{
	return _damage;
}
