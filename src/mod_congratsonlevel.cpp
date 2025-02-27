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
#include "Chat.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "WorldSessionMgr.h"

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

    CongratsAnnounce() : PlayerScript("CongratsAnnounce", {
        PLAYERHOOK_ON_LOGIN
    }) {}

    void OnPlayerLogin(Player* player)
    {
        // Announce Module
        if (col.congratsAnnounce)
            ChatHandler(player->GetSession()).SendSysMessage(col.acoreMessageId);
    }
};

class CongratsOnLevel : public PlayerScript
{
public:
    CongratsOnLevel() : PlayerScript("CongratsOnLevel", {
        PLAYERHOOK_ON_LEVEL_CHANGED
    }) { }

    // Level Up Rewards
    void OnPlayerLevelChanged(Player* player, uint8 oldLevel) override
    {
        // If enabled...
        if (col.congratsEnable)
        {
            uint8 level = player->GetLevel();
            uint32 money = 0;
            bool isRewardLevel = false;

            switch (level)
            {
                case 10:
                case 20:
                case 30:
                case 40:
                case 50:
                case 60:
                case 70:
                case 80:
                {
                    if (oldLevel < level)
                    {
                        isRewardLevel = true;
                        money = giveAward(player);
                    }
                }
                break;

                default:
                    break;
            }

            // Send message on every level up (if enabled)
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
                    {
    ss << "|cffFFFFFF[ |cffFF0000恭|cffFFA500喜|cffFFFF00你|cff00FF00升|cff00FFFF级|cff6A5ACD啦|cffFF00FF! |cffFFFFFF] : |cff4CFF00 " 
       << player->GetName() 
       << " |cffFFFFFF已达到 |cff4CFF00" 
       << std::to_string(player->GetLevel()) 
       << " 级|cffFFFFFF!";
    break;
}
                    case LOCALE_zhTW:
                    {
    ss << "|cffFFFFFF[ |cffFF0000恭|cffFFA500喜|cffFFFF00你|cff00FF00升|cff00FFFF級|cff6A5ACD啦|cffFF00FF! |cffFFFFFF] : |cff4CFF00 " 
       << player->GetName() 
       << " |cffFFFFFF已達到 |cff4CFF00" 
       << std::to_string(player->GetLevel()) 
       << " 級|cffFFFFFF!";
    break;
}
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
                sWorldSessionMgr->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());
            }

            // Always send message on reward level up
            if (isRewardLevel)
            {
                // Issue a server notification for the player on level up.
                std::ostringstream ss;
                switch (player->GetSession()->GetSessionDbLocaleIndex())
                {
                    case LOCALE_enUS:
                    case LOCALE_koKR:
                    case LOCALE_frFR:
                    case LOCALE_deDE:
                    case LOCALE_zhCN: // 简体中文
{
    ss << "|cffFFFFFF[ |cffFF0000恭|cffFFA500喜|cffFFFF00你|cff00FF00升|cff00FFFF级|cff6A5ACD啦|cffFF00FF! |cffFFFFFF] : |cff4CFF00 "
       << player->GetName()
       << " |cffFFFFFF已达到 |cff4CFF00"
       << static_cast<int>(player->GetLevel())
       << " 级|cffFFFFFF!";
    break;
}
case LOCALE_zhTW: // 繁体中文
{
    ss << "|cffFFFFFF[ |cffFF0000恭|cffFFA500喜|cffFFFF00你|cff00FF00升|cff00FFFF級|cff6A5ACD啦|cffFF00FF! |cffFFFFFF] : |cff4CFF00 "
       << player->GetName()
       << " |cffFFFFFF已達到 |cff4CFF00"
       << static_cast<int>(player->GetLevel())
       << " 級|cffFFFFFF!";
    break;
}
                    case LOCALE_ruRU:
                    {
                        ss << "|cffFFFFFF[ |cffFF0000C|cffFFA500O|cffFFFF00N|cff00FF00G|cff00FFFFR|cff6A5ACDA|cffFF00FFT|cff98FB98S|cffFF0000! |cffFFFFFF] : |cff4CFF00 " << player->GetName() << " |cffFFFFFFhas reached |cff4CFF00Level " << static_cast<int>(player->GetLevel()) << "|cffFFFFFF!";
                        break;
                    }
                    case LOCALE_esES:
                    case LOCALE_esMX:
                    {
                        ss << "|cffFFFFFF[ |cffFF0000F|cffFFA500E|cffFFFF00L|cff00FF00I|cff00FFFFC|cff6A5ACDI|cffFF00FFT|cff98FB98A|cff00FF00C|cff00FFFFI|cffFF0000O|cff00FF00N|cff00FFFFE|cffFF00FFS|cffFF0000! |cffFFFFFF] : |cff4CFF00 " << player->GetName() << " |cffFFFFFFha alcanzado |cff4CFF00el nivel " << static_cast<int>(player->GetLevel()) << "|cffFFFFFF!";
                    }
                    default:
                        break;
                }
                sWorldSessionMgr->SendServerMessage(SERVER_MSG_STRING, ss.str().c_str());

                // Issue a raid warning to the player
                std::ostringstream ss2;
                switch (player->GetSession()->GetSessionDbLocaleIndex())
                {
                    case LOCALE_enUS:
                    case LOCALE_koKR:
                    case LOCALE_frFR:
                    case LOCALE_deDE:
                    case LOCALE_zhCN: // 简体中文
{
    ss2 << "恭喜达到等级 " << static_cast<int>(player->GetLevel()) << "，" << player->GetName() 
        << "！您获得了 " << money << " 钱币和一些宝藏！";
    break;
}
case LOCALE_zhTW: // 繁体中文
{
    ss2 << "恭喜達到等級 " << static_cast<int>(player->GetLevel()) << "，" << player->GetName() 
        << "！您獲得了 " << money << " 錢幣和一些寶藏！";
    break;
}
                    case LOCALE_ruRU:
                    {
                        ss2 << "Congrats on Level " << static_cast<int>(player->GetLevel()) << " " << player->GetName() << "! You've been awarded " << money << " Copper and a few treasures!";
                        break;
                    }
                    case LOCALE_esES:
                    case LOCALE_esMX:
                    {
                        ss2 << "¡Felicidades por el nivel " << static_cast<int>(player->GetLevel()) << " " << player->GetName() << " Se le ha concedido " << money << " cobre y unos cuantos tesoros!";
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
    ModCongratsLevelWorldScript() : WorldScript("ModCongratsLevelWorldScript", {
        WORLDHOOK_ON_BEFORE_CONFIG_LOAD
    }) { }

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
