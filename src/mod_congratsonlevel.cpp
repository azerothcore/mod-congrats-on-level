/*

# Congrats On Level #

#### A module for AzerothCore by [StygianTheBest](https://github.com/StygianTheBest/AzerothCore-Content/tree/master/Modules)
------------------------------------------------------------------------------------------------------------------


### Description ###
------------------------------------------------------------------------------------------------------------------
This module rewards players when they reach specific levels. It has the option to reward gold, two items, and a
buff or any combination. It also announces to the world when a player levels up. All rewards can be set in the
config file for quick modifications.


### Features ###
------------------------------------------------------------------------------------------------------------------
- Announces player level up to world
- Awards the player for gaining new levels
- The player forfeits the rewards if their bags are full


### Data ###
------------------------------------------------------------------------------------------------------------------
- Type: Player/Server
- Script: CongratsOnLevel
- Config: Yes
    - Enable Module
    - Enable Module Announce
    - Set Items/Gold/Buffs Given At Each Level
- SQL: No


### Version ###
------------------------------------------------------------------------------------------------------------------
- v2017.08.06 - Release
- v2017.09.30 - Fix Level Display Bug. Update Strings.


### Credits ###
------------------------------------------------------------------------------------------------------------------
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


### License ###
------------------------------------------------------------------------------------------------------------------
- This code and content is released under the [GNU AGPL v3](https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3).

*/

#include "Configuration/Config.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"

class CongratsAnnounce : public PlayerScript
{

public:

    CongratsAnnounce() : PlayerScript("CongratsAnnounce") {}

    void OnLogin(Player* player)
    {
        // Announce Module
        if (sConfigMgr->GetBoolDefault("Congrats.Announce", true))
        {
                ChatHandler(player->GetSession()).SendSysMessage("This server is running the |cff4CFF00CongratsOnLevel |rmodule.");
         }
    }
};

class CongratsOnLevel : public PlayerScript
{

public:
    CongratsOnLevel() : PlayerScript("CongratsOnLevel") { }

    // Level Up Rewards
    void OnLevelChanged(Player* player, uint8 oldLevel) override
    {
        // If enabled...
        if (sConfigMgr->GetBoolDefault("Congrats.Enable", true)) {

            std::string level;
            uint32 money, item1, item2, spell;

            if (oldLevel < 10 && player->getLevel() == 10)
            {
                // Level 10
                const uint32 L101 = sConfigMgr->GetIntDefault("Congrats.L101", 0);
                const uint32 L102 = sConfigMgr->GetIntDefault("Congrats.L102", 0);
                const uint32 L10M = sConfigMgr->GetIntDefault("Congrats.L10M", 0);
                const uint32 L10S = sConfigMgr->GetIntDefault("Congrats.L10S", 0);

                level = "10";
                item1 = L101;
                item2 = L102;
                money = L10M;
                spell = L10S;
            }
            else if (oldLevel < 20 && player->getLevel() == 20)
            {
                // Level 20
                const uint32 L201 = sConfigMgr->GetIntDefault("Congrats.L201", 0);
                const uint32 L202 = sConfigMgr->GetIntDefault("Congrats.L202", 0);
                const uint32 L20M = sConfigMgr->GetIntDefault("Congrats.L20M", 0);
                const uint32 L20S = sConfigMgr->GetIntDefault("Congrats.L20S", 0);

                level = "20";
                item1 = L201;
                item2 = L202;
                money = L20M;
                spell = L20S;
            }
            else if (oldLevel < 30 && player->getLevel() == 30)
            {
                // Level 30
                const uint32 L301 = sConfigMgr->GetIntDefault("Congrats.L301", 0);
                const uint32 L302 = sConfigMgr->GetIntDefault("Congrats.L302", 0);
                const uint32 L30M = sConfigMgr->GetIntDefault("Congrats.L30M", 0);
                const uint32 L30S = sConfigMgr->GetIntDefault("Congrats.L30S", 0);

                level = "30";
                item1 = L301;
                item2 = L302;
                money = L30M;
                spell = L30S;
            }
            else if (oldLevel < 40 && player->getLevel() == 40)
            {
                // Level 40
                const uint32 L401 = sConfigMgr->GetIntDefault("Congrats.L401", 0);
                const uint32 L402 = sConfigMgr->GetIntDefault("Congrats.L402", 0);
                const uint32 L40M = sConfigMgr->GetIntDefault("Congrats.L40M", 0);
                const uint32 L40S = sConfigMgr->GetIntDefault("Congrats.L40S", 0);

                level = "40";
                item1 = L401;
                item2 = L402;
                money = L40M;
                spell = L40S;
            }
            else if (oldLevel < 50 && player->getLevel() == 50)
            {
                // Level 50
                const uint32 L501 = sConfigMgr->GetIntDefault("Congrats.L501", 0);
                const uint32 L502 = sConfigMgr->GetIntDefault("Congrats.L502", 0);
                const uint32 L50M = sConfigMgr->GetIntDefault("Congrats.L50M", 0);
                const uint32 L50S = sConfigMgr->GetIntDefault("Congrats.L50S", 0);

                level = "50";
                item1 = L501;
                item2 = L502;
                money = L50M;
                spell = L50S;
            }
            else if (oldLevel < 60 && player->getLevel() == 60)
            {
                // Level 60
                const uint32 L601 = sConfigMgr->GetIntDefault("Congrats.L601", 0);
                const uint32 L602 = sConfigMgr->GetIntDefault("Congrats.L602", 0);
                const uint32 L60M = sConfigMgr->GetIntDefault("Congrats.L60M", 0);
                const uint32 L60S = sConfigMgr->GetIntDefault("Congrats.L60S", 0);

                level = "60";
                item1 = L601;
                item2 = L602;
                money = L60M;
                spell = L60S;
            }
            else if (oldLevel < 70 && player->getLevel() == 70)
            {
                // Level 70
                const uint32 L701 = sConfigMgr->GetIntDefault("Congrats.L701", 0);
                const uint32 L702 = sConfigMgr->GetIntDefault("Congrats.L702", 0);
                const uint32 L70M = sConfigMgr->GetIntDefault("Congrats.L70M", 0);
                const uint32 L70S = sConfigMgr->GetIntDefault("Congrats.L70S", 0);

                level = "70";
                item1 = L701;
                item2 = L702;
                money = L70M;
                spell = L70S;
            }
            else if (oldLevel < 80 && player->getLevel() == 80)
            {
                // Level 80
                const uint32 L801 = sConfigMgr->GetIntDefault("Congrats.L801", 0);
                const uint32 L802 = sConfigMgr->GetIntDefault("Congrats.L802", 0);
                const uint32 L80M = sConfigMgr->GetIntDefault("Congrats.L80M", 0);
                const uint32 L80S = sConfigMgr->GetIntDefault("Congrats.L80S", 0);

                level = "80";
                item1 = L801;
                item2 = L802;
                money = L80M;
                spell = L80S;
            }

            // If enabled...
            if (sConfigMgr->GetBoolDefault("CongratsPerLevel.Enable", true))
            {
                // Issue a server notification for the player on level up.
                std::ostringstream ss;
                ss << "|cffFFFFFF[ |cffFF0000C|cffFFA500O|cffFFFF00N|cff00FF00G|cff00FFFFR|cff6A5ACDA|cffFF00FFT|cff98FB98S|cffFF0000! |cffFFFFFF] : |cff4CFF00 " << player->GetName() << " |cffFFFFFFhas reached |cff4CFF00Level " << std::to_string(player->getLevel()) << "|cffFFFFFF!";
                sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
            }

            // If level is defined, they hit a reward level.
            if (!level.empty())
            {
                // Issue a server notification for the player on level up.
                std::ostringstream ss;
                ss << "|cffFFFFFF[ |cffFF0000C|cffFFA500O|cffFFFF00N|cff00FF00G|cff00FFFFR|cff6A5ACDA|cffFF00FFT|cff98FB98S|cffFF0000! |cffFFFFFF] : |cff4CFF00 " << player->GetName() << " |cffFFFFFFhas reached |cff4CFF00Level " << level << "|cffFFFFFF!";
                sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());

                // Give the items to the player
                player->AddItem(item1, 1);				// Defined Item 1
                player->AddItem(item2, 1);				// Defined Item 2

                // Give gold to the player
                player->ModifyMoney(money*GOLD);		// Defined Gold

                // Buff the player
                player->CastSpell(player, spell);		// Defined Spell

                // Issue a raid warning to the player
                std::ostringstream ss2;
                ss2 << "Congrats on Level " << level << " " << player->GetName() << "! You've been awarded " << money << " gold and a few treasures!";
                player->GetSession()->SendNotification(SERVER_MSG_STRING, ss2.str().c_str());

                return;
            }
        }
    }
};


void AddCongratsOnLevelScripts()
{
	new CongratsAnnounce();
    new CongratsOnLevel();
}
