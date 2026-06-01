/**
 * Hello World Example
 * Created With Genesis-Code extension for Visual Studio Code
 * Use "Genesis Code: Compile" command to compile this program.
 **/
#include <genesis.h>
#include <resources.h>

int main()
{
    VDP_loadTileSet(bgtile.tileset, 1, DMA);
    VDP_setTileMapXY(BG_B, 1, 10, 1);
    while (1)
    {
        SYS_doVBlankProcess();
    }
    return (0);
}
