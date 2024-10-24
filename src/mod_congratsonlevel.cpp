/*

# Congrats On Level #

#### A module for AzerothCore (https://github.com/azerothcore/mod-congrats-on-level)
#### Originally by [StygianTheBest](https://github.com/StygianTheBest/AzerothCore-Content/tree/master/Modules)
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
- v2022.04.09 - Fixed deprecation warnings
- v2017.08.06 - Release
- v2017.09.30 - Fix Level Display Bug. Update Strings.


### Credits ###
------------------------------------------------------------------------------------------------------------------
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


### License ###
------------------------------------------------------------------------------------------------------------------
- This code and content is released under the [GNU AGPL v3](https://github.com/azerothcore/azerothcore-wotlk/blob/master/LICENSE-AGPL3).

*/

#include "Configuration/Config.h"
#include "ScriptMgr.h"
#include "Player.h"
#include "Chat.h"

struct COL
{
    uint32 acoreMessageId;
    bool congratsAnnounce, congratsEnable;
    bool CongratsPerLevelEnable;
};

COL col;

uint32 giveAward(Player* player)
{
    QueryResult result = WorldDatabase.Query("SELECT * FROM `mod_congrats_on_level_items` WHERE `level`={} AND (`race`={} OR `race`=0) AND (`class`={} OR `class`=0)", player->GetLevel(), player->getRace(), player->getClass());

    uint32 money = 0;

    if (result)
    {
        do
        {
            Field* fields = result->Fetch();
            if (fields[1].Get<uint32>() > 0)
            {
                player->ModifyMoney(fields[1].Get<uint32>() * GOLD);
                money += fields[1].Get<uint32>() * GOLD;
            }
            if (fields[2].Get<uint32>() > 0)
            {
                if (fields[3].Get<uint32>() == 0)
                    player->CastSpell(player, fields[2].Get<uint32>());
                else
                    player->learnSpell(fields[2].Get<uint32>());
            }
            if (fields[4].Get<uint32>() > 0)
                player->AddItem(fields[4].Get<uint32>(), 1);
            if (fields[5].Get<uint32>())
                player->AddItem(fields[5].Get<uint32>(), 1);
        }
        while (result->NextRow());

        return money;
    }
    return money;
}

class CongratsAnnounce : public PlayerScript
{

public:

    CongratsAnnounce() : PlayerScript("CongratsAnnounce") {}

    void OnLogin(Player* player)
    {
        // Announce Module
        if (col.congratsAnnounce)
        {
            ChatHandler(player->GetSession()).SendSysMessage(col.acoreMessageId);
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
        if (col.congratsEnable)
        {
            uint8 level = player->GetLevel();
            uint32 money = 0;

            switch (level)
            {
                case 10:
                {
                    if (oldLevel < 10)
                    {
                        money = giveAward(player);
                    }
                }
                break;

                case 20:
                {
                    if (oldLevel < 20)
                    {
                        money = giveAward(player);
                    }
                }
                break;

                case 30:
                {
                    if (oldLevel < 30)
                    {
                        money = giveAward(player);
                    }
                }
                break;

                case 40:
                {
                    if (oldLevel < 40)
                    {
                        money = giveAward(player);
                    }
                }
                break;

                case 50:
                {
                    if (oldLevel < 50)
                    {
                        money = giveAward(player);
                    }
                }
                break;

                case 60:
                {
                    if (oldLevel < 60)
                    {
                        money = giveAward(player);
                    }
                }
                break;

                case 70:
                {
                    if (oldLevel < 70)
                    {
                        money = giveAward(player);
                    }
                }
                break;

                case 80:
                {
                    if (oldLevel < 80)
                    {
                        money = giveAward(player);
                    }
                }
                break;

                default:
                    break;
            }

            // If enabled...
            if (col.CongratsPerLevelEnable)
            {
                // Issue a server notification for the player on level up.
                std::ostringstream ss;
                switch (player->GetSession()->GetSessionDbLocaleIndex())
                {
                    case LOCALE_enUS:
                    case LOCALE_koKR:
                    case LOCALE_frFR:
                    case LOCALE_deDE:
                    case LOCALE_zhCN:
                    case LOCALE_zhTW:
                    case LOCALE_ruRU:
                    {
                        ss << "|cffFFFFFF[ |cffFF0000C|cffFFA500O|cffFFFF00N|cff00FF00G|cff00FFFFR|cff6A5ACDA|cffFF00FFT|cff98FB98S|cffFF0000! |cffFFFFFF] : |cff4CFF00 " << player->GetName() << " |cffFFFFFFhas reached |cff4CFF00Level " << std::to_string(player->GetLevel()) << "|cffFFFFFF!";
                        break;
                    }
                    case LOCALE_esES:
                    case LOCALE_esMX:
                    {
                        ss << "|cffFFFFFF[ |cffFF0000F|cffFFA500E|cffFFFF00L|cff00FF00I|cff00FFFFC|cff6A5ACDI|cffFF00FFT|cff98FB98A|cff00FF00C|cff00FFFFI|cffFF0000O|cff00FF00N|cff00FFFFE|cffFF00FFS|cffFF0000! |cffFFFFFF] : |cff4CFF00 " << player->GetName() << " |cffFFFFFFha alcanzado |cff4CFF00el nivel " << std::to_string(player->GetLevel()) << "|cffFFFFFF!";
                    }
                    default:
                        break;
                }
                sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
            }

            // If level is defined, they hit a reward level.
            if (!level && col.CongratsPerLevelEnable)
            {
                // Issue a server notification for the player on level up.
                std::ostringstream ss;
                switch (player->GetSession()->GetSessionDbLocaleIndex())
                {
                    case LOCALE_enUS:
                    case LOCALE_koKR:
                    case LOCALE_frFR:
                    case LOCALE_deDE:
                    case LOCALE_zhCN:
                    case LOCALE_zhTW:
                    case LOCALE_ruRU:
                    {
                        ss << "|cffFFFFFF[ |cffFF0000C|cffFFA500O|cffFFFF00N|cff00FF00G|cff00FFFFR|cff6A5ACDA|cffFF00FFT|cff98FB98S|cffFF0000! |cffFFFFFF] : |cff4CFF00 " << player->GetName() << " |cffFFFFFFhas reached |cff4CFF00Level " << level << "|cffFFFFFF!";
                        break;
                    }
                    case LOCALE_esES:
                    case LOCALE_esMX:
                    {
                        ss << "|cffFFFFFF[ |cffFF0000F|cffFFA500E|cffFFFF00L|cff00FF00I|cff00FFFFC|cff6A5ACDI|cffFF00FFT|cff98FB98A|cff00FF00C|cff00FFFFI|cffFF0000O|cff00FF00N|cff00FFFFE|cffFF00FFS|cffFF0000! |cffFFFFFF] : |cff4CFF00 " << player->GetName() << " |cffFFFFFFha alcanzado |cff4CFF00el nivel " << level << "|cffFFFFFF!";
                    }
                    default:
                        break;
                }
                sWorld->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());

                // Issue a raid warning to the player
                std::ostringstream ss2;
                switch (player->GetSession()->GetSessionDbLocaleIndex())
                {
                    case LOCALE_enUS:
                    case LOCALE_koKR:
                    case LOCALE_frFR:
                    case LOCALE_deDE:
                    case LOCALE_zhCN:
                    case LOCALE_zhTW:
                    case LOCALE_ruRU:
                    {
                        ss2 << "Congrats on Level " << level << " " << player->GetName() << "! You've been awarded " << money << " gold and a few treasures!";
                        break;
                    }
                    case LOCALE_esES:
                    case LOCALE_esMX:
                    {
                        ss2 << "¡Felicidades por el nivel " << level << " " << player->GetName() << " Se le ha concedido " << money << " oro y unos cuantos tesoros!";
                    }
                    default:
                        break;
                }
                ChatHandler(player->GetSession()).SendNotification(SERVER_MSG_STRING, ss2.str().c_str());
                return;
            }
        }
    }
};

class ModCongratsLevelWorldScript : public WorldScript
{
public:
    ModCongratsLevelWorldScript() : WorldScript("ModCongratsLevelWorldScript") { }

    void OnBeforeConfigLoad(bool reload) override
    {
        if (!reload)
        {
            sConfigMgr->LoadModulesConfigs();
            col.acoreMessageId = sConfigMgr->GetOption<uint32>("Congrats.Acore.String.ID", 60000);
            col.congratsAnnounce = sConfigMgr->GetOption<uint32>("Congrats.Announce", 1);
            col.congratsEnable = sConfigMgr->GetOption<uint32>("Congrats.Enable", 1);
            col.CongratsPerLevelEnable = sConfigMgr->GetOption<uint32>("CongratsPerLevel.Enable", 1);
        }
    }
};

void AddCongratsOnLevelScripts()
{
    new CongratsAnnounce();
    new CongratsOnLevel();
    new ModCongratsLevelWorldScript();
}
