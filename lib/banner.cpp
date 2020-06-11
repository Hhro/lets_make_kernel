#include <fried/stdio.h>
#include <fried/string.h>
#include <banner.hpp>

const char *glyphs[] =
{
    "         ###  ### ###  # #   ##### ###   #  ##     ###  ",
    "         ###  ### ###  # #  #  #  ## #  #  #  #    ###  ",
    "         ###   #   # ########  #   ### #    ##      #   ",
    "          #            # #   #####    #    ###     #    ",
    "                     #######   #  #  # ####   # #       ",
    "         ###           # #  #  #  # #  # ##    #        ",
    "         ###           # #   ##### #   ### #### #       ",

    "   ##    ##                                            #",
    "  #        #   #   #    #                             # ",
    " #          #   # #     #                            #  ",
    " #          # ### ### #####   ###   #####           #   ",
    " #          #   # #     #     ###           ###    #    ",
    "  #        #   #   #    #      #            ###   #     ",
    "   ##    ##                   #             ###  #      ",

    "  ###     #    #####  ##### #      ####### ##### #######",
    " #   #   ##   #     ##     ##    # #      #     ##    # ",
    "# #   # # #         #      ##    # #      #          #  ",
    "#  #  #   #    #####  ##### ####### ##### ######    #   ",
    "#   # #   #   #            #     #       ##     #  #    ",
    " #   #    #   #      #     #     # #     ##     #  #    ",
    "  ###   ##### ####### #####      #  #####  #####   #    ",

    " #####  #####    #     ###      #           #     ##### ",
    "#     ##     #  # #    ###     #             #   #     #",
    "#     ##     #   #            #     #####     #        #",
    " #####  ######         ###   #                 #     ## ",
    "#     #      #   #     ###    #     #####     #     #   ",
    "#     ##     #  # #     #      #             #          ",
    " #####  #####    #     #        #           #       #   ",

    " #####    #   ######  ##### ###### ############## ##### ",
    "#     #  # #  #     ##     ##     ##      #      #     #",
    "# ### # #   # #     ##      #     ##      #      #      ",
    "# # # ##     ####### #      #     ######  #####  #  ####",
    "# #### ########     ##      #     ##      #      #     #",
    "#     ##     ##     ##     ##     ##      #      #     #",
    " ##### #     #######  ##### ###### ########       ##### ",

    "#     #  ###        ##    # #      #     ##     ########",
    "#     #   #         ##   #  #      ##   ####    ##     #",
    "#     #   #         ##  #   #      # # # ## #   ##     #",
    "#######   #         ####    #      #  #  ##  #  ##     #",
    "#     #   #   #     ##  #   #      #     ##   # ##     #",
    "#     #   #   #     ##   #  #      #     ##    ###     #",
    "#     #  ###   ##### #    # ########     ##     ########",

    "######  ##### ######  ##### ########     ##     ##     #",
    "#     ##     ##     ##     #   #   #     ##     ##  #  #",
    "#     ##     ##     ##         #   #     ##     ##  #  #",
    "###### #     #######  #####    #   #     ##     ##  #  #",
    "#      #   # ##   #        #   #   #     # #   # #  #  #",
    "#      #    # #    # #     #   #   #     #  # #  #  #  #",
    "#       #### ##     # #####    #    #####    #    ## ## ",

    "#     ##     ######## ##### #       #####    #          ",
    " #   #  #   #      #  #      #          #   # #         ",
    "  # #    # #      #   #       #         #  #   #        ",
    "   #      #      #    #        #        #               ",
    "  # #     #     #     #         #       #               ",
    " #   #    #    #      #          #      #               ",
    "#     #   #   ####### #####       # #####        #######",

    "  ###                                                   ",
    "  ###     ##   #####   ####  #####  ###### ######  #### ",
    "   #     #  #  #    # #    # #    # #      #      #    #",
    "    #   #    # #####  #      #    # #####  #####  #     ",
    "        ###### #    # #      #    # #      #      #  ###",
    "        #    # #    # #    # #    # #      #      #    #",
    "        #    # #####   ####  #####  ###### #       #### ",

    "                                                        ",
    " #    #    #        # #    # #      #    # #    #  #### ",
    " #    #    #        # #   #  #      ##  ## ##   # #    #",
    " ######    #        # ####   #      # ## # # #  # #    #",
    " #    #    #        # #  #   #      #    # #  # # #    #",
    " #    #    #   #    # #   #  #      #    # #   ## #    #",
    " #    #    #    ####  #    # ###### #    # #    #  #### ",

    "                                                        ",
    " #####   ####  #####   ####   ##### #    # #    # #    #",
    " #    # #    # #    # #         #   #    # #    # #    #",
    " #    # #    # #    #  ####     #   #    # #    # #    #",
    " #####  #  # # #####       #    #   #    # #    # # ## #",
    " #      #   #  #   #  #    #    #   #    #  #  #  ##  ##",
    " #       ### # #    #  ####     #    ####    ##   #    #",

    "                       ###     #     ###   ##    # # # #",
    " #    #  #   # ###### #        #        # #  #  # # # # ",
    "  #  #    # #      #  #        #        #     ## # # # #",
    "   ##      #      #  ##                 ##        # # # ",
    "   ##      #     #    #        #        #        # # # #",
    "  #  #     #    #     #        #        #         # # # ",
    " #    #    #   ######  ###     #     ###         # # # #"};

void banner(char *args) {

    int idx;
    int len = strlen(args) > 10 ? 10 : strlen(args);
   
    char buf[80];

    for(int i=0; i<7; i++){
        for(int j=0; j < len; j++){
            idx = (args[j] - 0x20) < 0 ? 0 : args[j] - 0x20;
            for(int k = 0; k < 7; k++){
                buf[j * 8 + k] = glyphs[(idx / 8 * 7) + i][(idx % 8 * 7) + k];
            }
            buf[j * 8 + 7] = 0x20;
        }
        for(int j = len*8-1; j >= 0; j--){
            if(buf[j] != 0x20)
                break;
            buf[j] = 0x0;
        }
        puts(buf);
    }

    return;
}