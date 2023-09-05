# ![logo](https://raw.githubusercontent.com/azerothcore/azerothcore.github.io/master/images/logo-github.png) AzerothCore

## mod-congrats-on-level

### This is a module for [AzerothCore](http://www.azerothcore.org)

- Latest build status with azerothcore:

[![Build Status](https://github.com/azerothcore/mod-congrats-on-level/workflows/core-build/badge.svg?branch=master&event=push)](https://github.com/azerothcore/mod-congrats-on-level)

### About the module

This module allows you to configure a series of prizes, by class, race and levels. To the extent that players reach these levels, they can obtain gold, spells, or items. If you don't want to deliver any of them, it's always possible to leave it at 0. All items were moved to the database. Inside the table, you could customize the prizes, however you want.

### Table structure

1. `level`: Level that the player must have to get the reward.
2. `money`: Amount of money to deliver, it can be 0.
3. `spell`: Id of the spell that you want to teach or cast, it can be 0.
4. `learn`: If it's 0, the spell is cast. If it is 1, it is learned.
5. `itemId1`: Id of the item that you want to deliver, it can be 0.
6. `itemId2`: Id of the item that you want to deliver, it can be 0.
7. `race`: 0 for all or specify race id.
8. `class`: 0 for all, or specify the class id.

| ID | className (enUS) |
|----|------------------|
| 1  | Warrior          |
| 2  | Paladin          |
| 3  | Hunter           |
| 4  | Rogue            |
| 5  | Priest           |
| 6  | Death Knight     |
| 7  | Shaman           |
| 8  | Mage             |
| 9  | Warlock          |
| 11 | Druid            |

| ID | Race .raceName (enUS) | Faction .name (enUS) |
|----|-----------------------|----------------------|
| 1  | Human                 | Alliance             |
| 2  | Orc                   | Horde                |
| 3  | Dwarf                 | Alliance             |
| 4  | Night Elf             | Alliance             |
| 5  | Undead                | Horde                |
| 6  | Tauren                | Horde                |
| 7  | Gnome                 | Alliance             |
| 8  | Troll                 | Horde                |
| 10 | Blood Elf             | Horde                |
| 11 | Draenei               | Alliance             |

### How to install
1. Simply place the module under the `modules` folder of your AzerothCore source folder.
2. Re-run cmake and launch a clean build of AzerothCore
3. Done :)

## Credits
- [SoulSeekkor](https://github.com/SoulSeekkor)
- [LordPsyan](https://bitbucket.org/lordpsyan/lordpsyan-patches)
- [Blizzard Entertainment](http://blizzard.com)
- [TrinityCore](https://github.com/TrinityCore/TrinityCore/blob/3.3.5/THANKS)
- [SunwellCore](http://www.azerothcore.org/pages/sunwell.pl/)
- [AzerothCore](https://github.com/AzerothCore/azerothcore-wotlk/graphs/contributors)
- [AzerothCore Discord](https://discord.gg/gkt4y2x)
- [EMUDevs](https://youtube.com/user/EmuDevs)
- [AC-Web](http://ac-web.org/)
- [ModCraft.io](http://modcraft.io/)
- [OwnedCore](http://ownedcore.com/)
- [OregonCore](https://wiki.oregon-core.net/)
- [Wowhead.com](http://wowhead.com)
- [AoWoW](https://wotlk.evowow.com/)
- [Stygianthebest]( http://stygianthebest.github.io)

- AzerothCore: [repository](https://github.com/azerothcore)
- [website](http://azerothcore.org/)
- [discord chat community](https://discord.gg/PaqQRkd)
