#ifndef WEAPON_H
#define WEAPON_H

class Weapon
{
public:
	Weapon(std::string name, int damage);
	~Weapon() {};

	static Weapon WeaponData[16];

	std::string getName();
	int getDamage();

private:
	std::string _name;
	int _damage;
};

#endif WEAPON_H