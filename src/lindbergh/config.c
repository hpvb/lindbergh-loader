#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "gpuvendor.h"

EmulatorConfig config = {0};

extern uint32_t elf_crc;

FILE *configFile = NULL;

#define CONFIG_PATH "lindbergh.conf"
#define MAX_LINE_LENGTH 1024

static char *getNextToken(char *buffer, char *seperator, char **saveptr)
{
    char *token = strtok_r(buffer, seperator, saveptr);
    if (token == NULL)
        return NULL;

    for (int i = 0; i < (int)strlen(token); i++)
    {
        if ((token[i] == '\n') || (token[i] == '\r'))
        {
            token[i] = 0;
        }
    }
    return token;
}

static int detectGame(uint32_t elf_crc)
{

    switch (elf_crc)
    {

    case SEGABOOT_2_4:
    {
        config.gameTitle = "Segaboot 2.4";
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case SEGABOOT_2_4_SYM:
    {
        config.gameTitle = "Segaboot 2.4 with symbols";
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case THE_HOUSE_OF_THE_DEAD_4_REVA:
    case THE_HOUSE_OF_THE_DEAD_4_REVA_TEST:
    {
        config.gameTitle = "The House of the Dead 4 Rev A";
        config.gameID = "SBLC";
        config.gameDVP = "DVP-0003A";
        config.gameType = SHOOTING;
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case THE_HOUSE_OF_THE_DEAD_4_REVB:
    case THE_HOUSE_OF_THE_DEAD_4_REVB_TEST:
    {
        config.gameTitle = "The House of the Dead 4 Rev B";
        config.gameID = "SBLC";
        config.gameDVP = "DVP-0003B";
        config.gameType = SHOOTING;
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case THE_HOUSE_OF_THE_DEAD_4_REVC:
    case THE_HOUSE_OF_THE_DEAD_4_REVC_TEST:
    {
        config.gameTitle = "The House of the Dead 4 Rev C";
        config.gameID = "SBLC";
        config.gameDVP = "DVP-0003C";
        config.gameType = SHOOTING;
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case THE_HOUSE_OF_THE_DEAD_4_SPECIAL:
    case THE_HOUSE_OF_THE_DEAD_4_SPECIAL_TEST:
    {
        config.gameTitle = "The House of the Dead 4 Special";
        config.emulateRideboard = 1;
        config.gameID = "SBLS";
        config.gameDVP = "DVP-0010";
        config.gameStatus = WORKING;
        config.width = 1024;
        config.height = 768;
        return 0;
    }
    break;

    case THE_HOUSE_OF_THE_DEAD_4_SPECIAL_REVB:
    case THE_HOUSE_OF_THE_DEAD_4_SPECIAL_REVB_TEST:
    {
        config.gameTitle = "The House of the Dead 4 Special Rev B";
        config.emulateRideboard = 1;
        config.gameDVP = "DVP-0010B";
        config.gameStatus = WORKING;
        config.width = 1024;
        config.height = 768;
        return 0;
    }
    break;

    case THE_HOUSE_OF_THE_DEAD_EX:
    case THE_HOUSE_OF_THE_DEAD_EX_TEST:

    {
        config.gameTitle = "The House of the Dead EX";
        config.gameStatus = WORKING;
        config.gameDVP = "DVP-0063";
        config.gameID = "SBRC";
        return 0;
    }
    break;

    case OUTRUN_2_SP_SDX_REVA:
    case OUTRUN_2_SP_SDX_REVA_TEST:
    case OUTRUN_2_SP_SDX_REVA_TEST2:
    {
        config.gameTitle = "Outrun 2 SP SDX Rev A";
        config.gameDVP = "DVP-0015A";
        config.gameID = "SBMB";
        config.emulateDriveboard = 1;
        config.emulateMotionboard = 1;
        config.gameStatus = WORKING;
        config.gameType = DRIVING;
        return 0;
    }
    break;

    case OUTRUN_2_SP_SDX:
    case OUTRUN_2_SP_SDX_TEST:
    {
        config.gameTitle = "Outrun 2 SP SDX";
        config.gameDVP = "DVP-0015";
        config.gameID = "SBMB";
        config.emulateDriveboard = 1;
        config.emulateMotionboard = 1;
        config.gameStatus = WORKING;
        config.gameType = DRIVING;
        return 0;
    }
    break;

    case VIRTUA_FIGHTER_5:
    {
        config.gameTitle = "Virtua Fighter 5";
        config.gameDVP = "DVP-0008";
        config.gameID = "SBLM";
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case VIRTUA_FIGHTER_5_REVA:
    {
        config.gameTitle = "Virtua Fighter 5 Rev A";
        config.gameDVP = "DVP-0008A";
        config.gameID = "SBLM";
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case VIRTUA_FIGHTER_5_REVB:
    {
        config.gameTitle = "Virtua Fighter 5 Rev B";
        config.gameDVP = "DVP-0008B";
        config.gameID = "SBLM";
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case VIRTUA_FIGHTER_5_REVE:
    {
        config.gameTitle = "Virtua Fighter 5 Rev E (Public Version C)";
        config.gameDVP = "DVP-0008E";
        config.gameID = "SBLM";
        config.gameStatus = WORKING;
        config.gameType = FIGHTING;
        return 0;
    }
    break;

    case VIRTUA_FIGHTER_5_EXPORT:
    {
        config.gameTitle = "Virtua Fighter 5 Export";
        config.gameDVP = "DVP-0043";
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case VIRTUA_FIGHTER_5_R:
    {
        config.gameTitle = "Virtua Fighter 5 R";
        config.gameDVP = "DVP-XXXX";
        config.gameID = "SBQU";
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case VIRTUA_FIGHTER_5_R_REVD:
    {
        config.gameTitle = "Virtua Fighter 5 R Rev D";
        config.gameDVP = "DVP-XXXX";
        config.gameID = "SBQU";
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case VIRTUA_FIGHTER_5_R_REVG:
    {
        config.gameTitle = "Virtua Fighter 5 R Rev G";
        config.gameDVP = "DVP-XXXX";
        config.gameID = "SBQU";
        config.gameStatus = WORKING;
        return 0;
    }
    break;
	
    case VIRTUA_FIGHTER_5_FINAL_SHOWDOWN:
    {
        config.gameTitle = "Virtua Fighter 5 Final Showdown";
        config.gameDVP = "DVP-SBUV";
        config.gameID = "SBUV";
        return 0;
    }
    break;

    case VIRTUA_FIGHTER_5_FINAL_SHOWDOWN_REVA:
    {
        config.gameTitle = "Virtua Fighter 5 Final Showdown REV A";
        config.gameDVP = "DVP-5019A";
        config.gameID = "SBUV";
        return 0;
    }
    break;

    case VIRTUA_FIGHTER_5_FINAL_SHOWDOWN_REVB:
    {
        config.gameTitle = "Virtua Fighter 5 Final Showdown REV B";
        config.gameDVP = "DVP-5019B";
        config.gameID = "SBUV";
        return 0;
    }
    break;

    case VIRTUA_FIGHTER_5_FINAL_SHOWDOWN_REVB_6000:
    {
        config.gameTitle = "Virtua Fighter 5 Final Showdown REV B ver 6.0000";
        config.gameDVP = "DVP-5020";
        config.gameID = "SBUV";
        return 0;
    }
    break;

    case LETS_GO_JUNGLE:
    {
        config.gameTitle = "Let's Go Jungle! Lost on the Island of Spice!";
        config.gameDVP = "DVP-0011";
        config.gameID = "SBLU";
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case LETS_GO_JUNGLE_SPECIAL:
    {
        config.gameTitle = "Let's Go Jungle! Special!";
        config.emulateRideboard = 1;
        config.gameID = "SBNR";
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case AFTER_BURNER_CLIMAX:
    {
        config.gameTitle = "After Burner Climax";
        config.gameDVP = "DVP-0009";
        config.gameID = "SBLR";
        config.gameStatus = WORKING;
        config.jvsIOType = SEGA_TYPE_1;
        config.gameType = ABC;
        return 0;
    }
    break;

    case AFTER_BURNER_CLIMAX_REVA:
    {
        config.gameTitle = "After Burner Climax Rev A";
        config.gameDVP = "DVP-0009A";
        config.gameID = "SBLR";
        config.gameStatus = WORKING;
        config.jvsIOType = SEGA_TYPE_1;
        config.gameType = ABC;
        return 0;
    }
    break;

    case AFTER_BURNER_CLIMAX_REVB:
    {
        config.gameTitle = "After Burner Climax Rev B";
        config.gameDVP = "DVP-0009B";
        config.gameID = "SBLR";
        config.gameStatus = WORKING;
        config.jvsIOType = SEGA_TYPE_1;
        config.gameType = ABC;
        return 0;
    }
    break;

    case AFTER_BURNER_CLIMAX_SDX:
    {
        config.gameTitle = "After Burner Climax SDX";
        config.gameDVP = "DVP-0018-SDX";
        config.gameID = "SBMN";
        config.gameStatus = WORKING;
        config.jvsIOType = SEGA_TYPE_1;
        config.gameType = ABC;
        return 0;
    }
    break;

    case AFTER_BURNER_CLIMAX_SDX_REVA:
    {
        config.gameTitle = "After Burner Climax SDX Rev A";
        config.gameDVP = "DVP-0018A-SDX";
        config.gameStatus = WORKING;
        config.jvsIOType = SEGA_TYPE_1;
        config.gameType = ABC;
        return 0;
    }
    break;

    case AFTER_BURNER_CLIMAX_SE:
    {
        config.gameTitle = "After Burner Climax SE";
        config.gameDVP = "DVP-0031";
        config.gameID = "SBLR";
        config.gameStatus = WORKING;
        config.jvsIOType = SEGA_TYPE_1;
        config.gameType = ABC;
        return 0;
    }
    break;

    case AFTER_BURNER_CLIMAX_SE_REVA:
    {
        config.gameTitle = "After Burner Climax SE Rev A";
        config.gameDVP = "DVP-0031A";
        config.gameID = "SBLR";
        config.gameStatus = WORKING;
        config.jvsIOType = SEGA_TYPE_1;
        config.gameType = ABC;
        return 0;
    }
    break;

    case INITIALD_4_REVA:
    {
        config.gameTitle = "Initial D Arcade Stage 4 Rev A";
        config.gameStatus = WORKING;
        config.gameDVP = "DVP-0019A";
        config.gameID = "SBML";
        config.gameType = DRIVING;
        return 0;
    }
    break;

    case INITIALD_4_REVB:
    {
        config.gameTitle = "Initial D Arcade Stage 4 Rev B";
        config.gameStatus = WORKING;
        config.gameDVP = "DVP-0019B";
        config.gameID = "SBML";
        config.gameType = DRIVING;
        return 0;
    }
    break;

    case INITIALD_4_REVC:
    {
        config.gameTitle = "Initial D Arcade Stage 4 Rev C";
        config.gameStatus = WORKING;
        config.gameDVP = "DVP-0019C";
        config.gameID = "SBML";
        config.gameType = DRIVING;
        return 0;
    }
    break;

    case INITIALD_4_REVD:
    {
        config.gameTitle = "Initial D Arcade Stage 4 Rev D";
        config.gameStatus = WORKING;
        config.gameDVP = "DVP-0019D";
        config.gameID = "SBML";
        config.gameType = DRIVING;
        return 0;
    }
    break;

    case INITIALD_4_REVG:
    {
        config.gameTitle = "Initial D Arcade Stage 4 Rev G";
        config.gameStatus = WORKING;
        config.gameDVP = "DVP-0019G";
        config.gameID = "SBML";
        config.gameType = DRIVING;
        return 0;
    }
    break;

    case INITIALD_4_EXP_REVB:
    {
        config.gameTitle = "Initial D Arcade Stage 4 Export Rev B";
        config.gameStatus = WORKING;
        config.gameDVP = "DVP-0030B";
        config.gameID = "SBNK";
        config.gameType = DRIVING;
        return 0;
    }
    break;

    case INITIALD_4_EXP_REVC:
    {
        config.gameTitle = "Initial D Arcade Stage 4 Export Rev C";
        config.gameStatus = WORKING;
        config.gameDVP = "DVP-0030C";
        config.gameID = "SBNK";
        config.gameType = DRIVING;
        return 0;
    }
    break;

    case INITIALD_4_EXP_REVD:
    {
        config.gameTitle = "Initial D Arcade Stage 4 Export Rev D";
        config.gameStatus = WORKING;
        config.gameDVP = "DVP-0030D";
        config.gameID = "SBNK";
        config.gameType = DRIVING;
        return 0;
    }
    break;

    case SEGA_RACE_TV:
    {
        config.gameTitle = "SEGA Race TV";
        config.emulateDriveboard = 1;
        config.gameDVP = "DVP-0044";
        config.gameStatus = WORKING;
        config.gameType = DRIVING;
        return 0;
    }
    break;

    case RAMBO:
    {
        config.gameTitle = "Rambo";
        config.gameDVP = "DVP-0069";
        config.gameID = "SBQL";
        config.gameType = SHOOTING;
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case R_TUNED:
    {
        config.gameTitle = "R Tuned";
        config.emulateDriveboard = 1;
        config.gameStatus = WORKING;
        config.gameType = DRIVING;
        return 0;
    }
    break;

    case TOO_SPICY:
    case TOO_SPICY_TEST:
    {
        config.gameTitle = "Too Spicy";
        config.gameDVP = "DVP-0027A";
        config.gameID = "SBMV";
        config.gameStatus = WORKING;
        config.gameType = SHOOTING;
        return 0;
    }
    break;

    case VIRTUA_TENNIS_3:
    case VIRTUA_TENNIS_3_TEST:
    {
        config.gameTitle = "Virtua Tennis 3";
        config.gameDVP = "DVP-0005";
        config.gameID = "SBKX";
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case VIRTUA_TENNIS_3_REVA:
    case VIRTUA_TENNIS_3_REVA_TEST:
    {
        config.gameTitle = "Virtua Tennis 3 Rev A";
        config.gameDVP = "DVP-0005A";
        config.gameID = "SBKX";
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case VIRTUA_TENNIS_3_REVB:
    case VIRTUA_TENNIS_3_REVB_TEST:
    {
        config.gameTitle = "Virtua Tennis 3 Rev B";
        config.gameDVP = "DVP-0005B";
        config.gameID = "SBKX";
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case VIRTUA_TENNIS_3_REVC:
    case VIRTUA_TENNIS_3_REVC_TEST:
    {
        config.gameTitle = "Virtua Tennis 3 Rev C";
        config.gameDVP = "DVP-0005C";
        config.gameID = "SBKX";
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case PRIMEVAL_HUNT:
    {
        config.gameTitle = "Primeval Hunt";
        config.gameDVP = "DVP-0048A";
        config.gameID = "SBPP";
        config.gameStatus = WORKING;
        config.gameType = SHOOTING;
        return 0;
    }
    break;

    case GHOST_SQUAD_EVOLUTION:
    {
        config.gameTitle = "Ghost Squad Evolution";
        config.gameStatus = WORKING;
        config.gameDVP = "DVP-0029A";
        config.gameID = "SBNJ";
        config.jvsIOType = SEGA_TYPE_1;
        return 0;
    }
    break;

    case INITIALD_5_JAP_REVA:
    {
        config.gameTitle = "Initial D Arcade Stage 5 Rev A";
        config.gameDVP = "DVP-0070A";
        config.gameID = "SBQZ";
        config.gameStatus = WORKING;
        config.gameType = DRIVING;
        return 0;
    }
    break;

    case INITIALD_5_JAP_REVF:
    {
        config.gameTitle = "Initial D Arcade Stage 5 Rev F";
        config.gameDVP = "DVP-0070F";
        config.gameID = "SBQZ";
        config.gameStatus = WORKING;
        config.gameType = DRIVING;
        return 0;
    }
    break;

    case INITIALD_5_EXP_30:
    {
        config.gameTitle = "Initial D5 Ver 2.0";
        config.gameStatus = WORKING;
        config.gameDVP = "DVP-0075";
        config.gameID = "SBTS";
        config.gameType = DRIVING;
        return 0;
    }
    break;

    case INITIALD_5_EXP_40:
    {
        config.gameTitle = "Initial D5 5 Ver 4.0";
        config.gameDVP = "DVP-0084A";
        config.gameID = "SBQN";
        config.gameStatus = WORKING;
        config.gameType = DRIVING;
        return 0;
    }
    break;

    case HUMMER:
    {
        config.gameTitle = "Hummer";
        config.gameID = "SBQN";
        config.gameDVP = "DVP-0057B";
        config.gameType = DRIVING;
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case HUMMER_SDLX:
    {
        config.gameTitle = "Hummer SDLX";
        config.gameID = "SBST";
        config.gameDVP = "DVP-0057";
        config.gameType = DRIVING;
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case HUMMER_EXTREME:
    {
        config.gameTitle = "Hummer Extreme";
        config.gameID = "SBST";
        config.gameDVP = "DVP-0079";
        config.gameType = DRIVING;
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case HUMMER_EXTREME_MDX:
    {
        config.gameTitle = "Hummer Extreme MDX";
        config.gameID = "SBST";
        config.gameDVP = "DVP-0083";
        config.gameType = DRIVING;
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case LETS_GO_JUNGLE_REVA:
    {
        config.gameTitle = "Let's Go Jungle! Lost on the Island of Spice! Rev A";
        config.gameDVP = "DVP-0011A";
        config.gameID = "SBLU";
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    case HARLEY_DAVIDSON:
    {
        config.gameTitle = "Harley Davidson";
        config.gameType = HARLEY;
        config.gameDVP = "DVP-5007";
        config.gameStatus = WORKING;
        return 0;
    }
    break;

    default:
    {
        config.crc32 = UNKNOWN;
    }
    break;
    }

    return 1;
}

char *getGameName()
{
    return config.gameTitle;
}

char *getDVPName()
{
    return config.gameDVP;
}

char *getGameID()
{
    return config.gameID;
}

int readConfig(FILE *configFile, EmulatorConfig *config)
{
    char buffer[MAX_LINE_LENGTH];
    char *saveptr = NULL;

    while (fgets(buffer, MAX_LINE_LENGTH, configFile))
    {

        /* Check for comments */
        if (buffer[0] == '#' || buffer[0] == 0 || buffer[0] == ' ' || buffer[0] == '\r' || buffer[0] == '\n')
            continue;

        char *command = getNextToken(buffer, " ", &saveptr);

        if (strcmp(command, "WIDTH") == 0)
            config->width = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "HEIGHT") == 0)
            config->height = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "EEPROM_PATH") == 0)
            strcpy(config->eepromPath, getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "SRAM_PATH") == 0)
            strcpy(config->eepromPath, getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "EMULATE_RIDEBOARD") == 0)
            config->emulateRideboard = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "EMULATE_DRIVEBOARD") == 0)
            config->emulateDriveboard = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "EMULATE_MOTIONBOARD") == 0)
            config->emulateMotionboard = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "FULLSCREEN") == 0)
            config->fullscreen = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "NO_SDL") == 0)
            config->noSDL = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "EMULATE_JVS") == 0)
            config->emulateJVS = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "JVS_PATH") == 0)
            strcpy(config->jvsPath, getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "SERIAL_1_PATH") == 0)
            strcpy(config->serial1Path, getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "SERIAL_2_PATH") == 0)
            strcpy(config->serial2Path, getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "FREEPLAY") == 0)
            config->freeplay = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "LINDBERGH_COLOUR") == 0)
        {
            char colour[256];
            strcpy(colour, getNextToken(NULL, " ", &saveptr));
            if (strcmp(colour, "RED") == 0)
                config->lindberghColour = RED;
        }

        else if (strcmp(command, "REGION") == 0)
        {
            char region[256];
            strcpy(region, getNextToken(NULL, " ", &saveptr));
            if (strcmp(region, "JP") == 0)
                config->region = JP;
            else if (strcmp(region, "US") == 0)
                config->region = US;
            else
                config->region = EX;
        }

        else if (strcmp(command, "DEBUG_MSGS") == 0)
            config->showDebugMessages = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "HUMMER_FLICKER_FIX") == 0)
            config->hummerFlickerFix = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "KEEP_ASPECT_RATIO") == 0)
            config->keepAspectRatio = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "GPU_VENDOR") == 0)
            config->GPUVendor = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "OUTRUN_LENS_GLARE_ENABLED") == 0)
            config->outrunLensGlareEnabled = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "FPS_LIMITER_ENABLED") == 0)
            config->fpsLimiter = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "FPS_TARGET") == 0)
            config->fpsTarget = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "LGJ_RENDER_WITH_MESA") == 0)
            config->lgjRenderWithMesa = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "PRIMEVAL_HUNT_MODE") == 0)
            config->phMode = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "TEST_KEY") == 0)
            config->keymap.test = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "PLAYER_1_START_KEY") == 0)
            config->keymap.player1.start = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "PLAYER_1_SERVICE_KEY") == 0)
            config->keymap.player1.service = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "PLAYER_1_COIN_KEY") == 0)
            config->keymap.player1.coin = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "PLAYER_1_UP_KEY") == 0)
            config->keymap.player1.up = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "PLAYER_1_DOWN_KEY") == 0)
            config->keymap.player1.down = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "PLAYER_1_LEFT_KEY") == 0)
            config->keymap.player1.left = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "PLAYER_1_RIGHT_KEY") == 0)
            config->keymap.player1.right = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "PLAYER_1_BUTTON_1_KEY") == 0)
            config->keymap.player1.button1 = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "PLAYER_1_BUTTON_2_KEY") == 0)
            config->keymap.player1.button2 = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "PLAYER_1_BUTTON_3_KEY") == 0)
            config->keymap.player1.button3 = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "PLAYER_1_BUTTON_4_KEY") == 0)
            config->keymap.player1.button4 = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "PLAYER_1_BUTTON_5_KEY") == 0)
            config->keymap.player1.button5 = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "PLAYER_1_BUTTON_6_KEY") == 0)
            config->keymap.player1.button6 = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "PLAYER_1_BUTTON_7_KEY") == 0)
            config->keymap.player1.button7 = atoi(getNextToken(NULL, " ", &saveptr));

        else if (strcmp(command, "PLAYER_1_BUTTON_8_KEY") == 0)
            config->keymap.player1.button8 = atoi(getNextToken(NULL, " ", &saveptr));

        // Player 1 controls
        else if (strcmp(command, "PLAYER_1_BUTTON_START") == 0)
            strncpy(config->arcadeInputs.player1_button_start, getNextToken(NULL, " ", &saveptr),
                    INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_1_BUTTON_SERVICE") == 0)
            strncpy(config->arcadeInputs.player1_button_service, getNextToken(NULL, " ", &saveptr),
                    INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_1_BUTTON_UP") == 0)
            strncpy(config->arcadeInputs.player1_button_up, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_1_BUTTON_DOWN") == 0)
            strncpy(config->arcadeInputs.player1_button_down, getNextToken(NULL, " ", &saveptr),
                    INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_1_BUTTON_LEFT") == 0)
            strncpy(config->arcadeInputs.player1_button_left, getNextToken(NULL, " ", &saveptr),
                    INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_1_BUTTON_RIGHT") == 0)
            strncpy(config->arcadeInputs.player1_button_right, getNextToken(NULL, " ", &saveptr),
                    INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_1_BUTTON_1") == 0)
            strncpy(config->arcadeInputs.player1_button_1, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_1_BUTTON_2") == 0)
            strncpy(config->arcadeInputs.player1_button_2, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_1_BUTTON_3") == 0)
            strncpy(config->arcadeInputs.player1_button_3, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_1_BUTTON_4") == 0)
            strncpy(config->arcadeInputs.player1_button_4, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_1_BUTTON_5") == 0)
            strncpy(config->arcadeInputs.player1_button_5, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_1_BUTTON_6") == 0)
            strncpy(config->arcadeInputs.player1_button_6, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_1_BUTTON_7") == 0)
            strncpy(config->arcadeInputs.player1_button_7, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_1_BUTTON_8") == 0)
            strncpy(config->arcadeInputs.player1_button_8, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_1_BUTTON_9") == 0)
            strncpy(config->arcadeInputs.player1_button_9, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_1_BUTTON_10") == 0)
            strncpy(config->arcadeInputs.player1_button_10, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);

        // Player 2 controls
        else if (strcmp(command, "PLAYER_2_BUTTON_START") == 0)
            strncpy(config->arcadeInputs.player2_button_start, getNextToken(NULL, " ", &saveptr),
                    INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_2_BUTTON_SERVICE") == 0)
            strncpy(config->arcadeInputs.player2_button_service, getNextToken(NULL, " ", &saveptr),
                    INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_2_BUTTON_UP") == 0)
            strncpy(config->arcadeInputs.player2_button_up, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_2_BUTTON_DOWN") == 0)
            strncpy(config->arcadeInputs.player2_button_down, getNextToken(NULL, " ", &saveptr),
                    INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_2_BUTTON_LEFT") == 0)
            strncpy(config->arcadeInputs.player2_button_left, getNextToken(NULL, " ", &saveptr),
                    INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_2_BUTTON_RIGHT") == 0)
            strncpy(config->arcadeInputs.player2_button_right, getNextToken(NULL, " ", &saveptr),
                    INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_2_BUTTON_1") == 0)
            strncpy(config->arcadeInputs.player2_button_1, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_2_BUTTON_2") == 0)
            strncpy(config->arcadeInputs.player2_button_2, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_2_BUTTON_3") == 0)
            strncpy(config->arcadeInputs.player2_button_3, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_2_BUTTON_4") == 0)
            strncpy(config->arcadeInputs.player2_button_4, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_2_BUTTON_5") == 0)
            strncpy(config->arcadeInputs.player2_button_5, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_2_BUTTON_6") == 0)
            strncpy(config->arcadeInputs.player2_button_6, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_2_BUTTON_7") == 0)
            strncpy(config->arcadeInputs.player2_button_7, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_2_BUTTON_8") == 0)
            strncpy(config->arcadeInputs.player2_button_8, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_2_BUTTON_9") == 0)
            strncpy(config->arcadeInputs.player2_button_9, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "PLAYER_2_BUTTON_10") == 0)
            strncpy(config->arcadeInputs.player2_button_10, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);

        // Analogue inputs
        else if (strcmp(command, "ANALOGUE_1") == 0)
            strncpy(config->arcadeInputs.analogue_1, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "ANALOGUE_2") == 0)
            strncpy(config->arcadeInputs.analogue_2, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "ANALOGUE_3") == 0)
            strncpy(config->arcadeInputs.analogue_3, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "ANALOGUE_4") == 0)
            strncpy(config->arcadeInputs.analogue_4, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "ANALOGUE_5") == 0)
            strncpy(config->arcadeInputs.analogue_5, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "ANALOGUE_6") == 0)
            strncpy(config->arcadeInputs.analogue_6, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "ANALOGUE_7") == 0)
            strncpy(config->arcadeInputs.analogue_7, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);
        else if (strcmp(command, "ANALOGUE_8") == 0)
            strncpy(config->arcadeInputs.analogue_8, getNextToken(NULL, " ", &saveptr), INPUT_STRING_LENGTH - 1);

        else if (strcmp(command, "INPUT_MODE") == 0)
            config->inputMode = atoi(getNextToken(NULL, " ", &saveptr));

        else
            printf("Error: Unknown settings command %s\n", command);
    }

    return 0;
}

KeyMapping getDefaultKeymap()
{
    KeyMapping defaultKeyMapping;
    defaultKeyMapping.test = 28;
    defaultKeyMapping.player1.start = 10;
    defaultKeyMapping.player1.service = 39;
    defaultKeyMapping.player1.coin = 14;
    defaultKeyMapping.player1.up = 111;
    defaultKeyMapping.player1.down = 116;
    defaultKeyMapping.player1.left = 113;
    defaultKeyMapping.player1.right = 114;
    defaultKeyMapping.player1.button1 = 24;
    defaultKeyMapping.player1.button2 = 25;
    defaultKeyMapping.player1.button3 = 26;
    defaultKeyMapping.player1.button4 = 27; // R
    defaultKeyMapping.player1.button5 = 40; // D
    defaultKeyMapping.player1.button6 = 41;
    defaultKeyMapping.player1.button7 = 42;
    defaultKeyMapping.player1.button8 = 43;
    defaultKeyMapping.player2.start = 60;
    defaultKeyMapping.player2.service = 61;
    defaultKeyMapping.player2.coin = 15;
    defaultKeyMapping.player2.up = 54;
    defaultKeyMapping.player2.down = 53;
    defaultKeyMapping.player2.left = 55;
    defaultKeyMapping.player2.right = 56;
    defaultKeyMapping.player2.button1 = 52;
    defaultKeyMapping.player2.button2 = 57;
    defaultKeyMapping.player2.button3 = 58;
    defaultKeyMapping.player2.button4 = 59; // ,
    defaultKeyMapping.player2.button5 = 37; // CTRL
    return defaultKeyMapping;
}

int initConfig()
{
    config.emulateRideboard = 0;
    config.emulateDriveboard = 0;
    config.emulateMotionboard = 0;
    config.emulateJVS = 1;
    config.fullscreen = 0;
    config.lindberghColour = YELLOW;
    strcpy(config.eepromPath, "eeprom.bin");
    strcpy(config.sramPath, "sram.bin");
    strcpy(config.jvsPath, "/dev/ttyUSB0");
    strcpy(config.serial1Path, "/dev/ttyS0");
    strcpy(config.serial2Path, "/dev/ttyS1");
    config.width = 640;
    config.height = 480;
    config.region = -1;
    config.freeplay = -1;
    config.showDebugMessages = 0;
    config.hummerFlickerFix = 0;
    config.keepAspectRatio = 0;
    config.gameTitle = "Unknown game";
    config.gameID = "XXXX";
    config.gameDVP = "DVP-XXXX";
    config.gameType = SHOOTING;
    config.keymap = getDefaultKeymap();
    config.jvsIOType = SEGA_TYPE_3;
    config.outrunLensGlareEnabled = 1;
    config.GPUVendor = AUTO_DETECT_GPU;
    config.fpsLimiter = 0;
    config.fpsTarget = 60;
    config.lgjRenderWithMesa = 1;
    config.noSDL = 0;
    config.phMode = 1;
    config.crc32 = elf_crc;
    if (detectGame(config.crc32) != 0)
    {
        printf("Warning: Unsure what game with CRC 0x%X is. Please submit this new game to the GitHub repository: "
               "https://github.com/lindbergh-loader/lindbergh-loader/issues/"
               "new?title=Please+add+new+game+0x%X&body=I+tried+to+launch+the+following+game:\n",
               config.crc32, config.crc32);
    }

    config.inputMode = 0; // Default to all inputs

    configFile = fopen(CONFIG_PATH, "r");

    if (configFile == NULL)
    {
        printf("Warning: Cannot open %s, using default values.\n", CONFIG_PATH);
        return 1;
    }

    readConfig(configFile, &config);

    fclose(configFile);

    return 0;
}

EmulatorConfig *getConfig()
{
    return &config;
}
