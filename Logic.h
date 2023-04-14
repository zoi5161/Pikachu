#include "Header.h"

// Reset
void From(int height, int width, int idxNum[][widthB+2], int line[][widthB+2], int lineOut[][widthB+3], int lineEnd[][widthB+2], int resetNum[][widthB+2], int resetLine[][widthB+2], int resetLineOut[][widthB+3], int resetLineEnd[][widthB+2])
{
    for(int i = 0; i < height + 2; i++)
        for(int j = 0; j < width + 2; j++)
        {  
            if(i%5 != 1 || j%10 !=1)
                resetNum[i][j] = idxNum[i][j];
            resetLine[i][j] = line[i][j];
            resetLineOut[i][j] = lineOut[i][j];
            resetLineEnd[i][j] = lineEnd[i][j];
        }
}

void To(int height, int width, int idxNum[][widthB+2], int line[][widthB+2], int lineOut[][widthB+3], int lineEnd[][widthB+2], int resetNum[][widthB+2], int resetLine[][widthB+2], int resetLineOut[][widthB+3], int resetLineEnd[][widthB+2])
{
    for(int i = 0; i < height + 2; i++)
        for(int j = 0; j < width + 2; j++)
        {
            if(i%5 != 1 || j%10 !=1)
                idxNum[i][j] = resetNum[i][j];
            line[i][j] = resetLine[i][j];
            lineOut[i][j] = resetLineOut[i][j];
            lineEnd[i][j] = resetLineEnd[i][j];
        }
}

void change(int height, int width, int last, int obj[27], int randomObj, char idxObj[][widthB+2],int idxNum[][widthB+2], int line[][widthB+2], int lineOut[][widthB+3], int lineEnd[][widthB+2], int resetNum[][widthB+2], int resetLine[][widthB+2], int resetLineOut[][widthB+3], int resetLineEnd[][widthB+2])
{
    for(int i=65; i<=90; i++)
        obj[i] = 0;

    for(int i=0; i<last; i++)
        obj[(rand()%26)+65] += 2;

    for(int i=3; i<height+2; i += 5)
        for(int j=5; j<width+2; j += 10)
        {
            if(idxNum[i][j] != 300)
            {
                randomObj = (rand()%26)+65;
                while(obj[randomObj] == 0)
                    randomObj = (rand()%26)+65;

                idxObj[i][j] = char(randomObj);
                idxNum[i-2][j-4] = randomObj;
                obj[randomObj]--;
            }
        }
}

// Check how to connect and draw
bool checkLineCol(ippxy, int width, int idxNum[][widthB+2], int line[][widthB+2], int lineOut[][widthB+3], int lineEnd[][widthB+2])
{
    int flag = 0;
    if (x == prevX)
    {
        for(int i = max(prevY, y) - 5; i >= min(prevY, y) + 5; i -= 5)
        {
            if(idxNum[i][x] != 300)
            {
                flag = 1;
                break;
            }
        }
        if(!flag)
        {
            for(int j = min(prevY, y) + 3; j <= max(prevY, y) + 1; j++)
                line[j][x+4] = 2;
            lineEnd[min(prevY, y)+3][x+4] = 1;
            lineEnd[max(prevY, y)+1][x+4] = 2;
            return true;
        }
    }
    if(x == prevX && (x == 1 || x == width - 8))
    {
        if(x == 1)
        {
            for(int i = 0; i <= x+3; i++)
            {
                line[min(prevY, y)+2][i] = 2;
                line[max(prevY, y)+2][i] = 2;
            }
            for(int i = min(prevY, y) + 3; i <= max(prevY, y) + 1; i++)
                lineOut[i][min(prevX,x)-1] = 2;
            lineEnd[min(prevY, y)+2][x+3] = 3;
            lineEnd[max(prevY, y)+2][x+3] = 3;
        }
        else
        {
            for(int i = x+5; i <= x+9; i++)
            {
                line[min(prevY, y)+2][i] = 2;
                line[max(prevY, y)+2][i] = 2;
            }
            for(int i = min(prevY, y) + 3; i <= max(prevY, y) + 1; i++)
                lineOut[i][width+1] = 2;
                
            lineEnd[min(prevY, y)+2][x+5] = 4;
            lineEnd[max(prevY, y)+2][x+5] = 4;
        }
        return true;
    }
    return false;
}

bool checkLineRow(ippxy, int height, int idxNum[][widthB+2], int line[][widthB+2], int lineOut[][widthB+3], int lineEnd[][widthB+2])
{
    int flag = 0;
    if (y == prevY)
    {
        for(int i = max(prevX, x) - 10; i >= min(prevX, x) + 10; i -= 10)
        {
            if(idxNum[y][i] != 300)
            {
                flag = 1;
                break;
            }
        }

        if(!flag)
        {
            for(int j = min(prevX, x) + 5; j <= max(prevX, x) + 3; j++)
                line[y+2][j] = 2;
            lineEnd[y+2][min(prevX, x)+5] = 4;
            lineEnd[y+2][max(prevX, x)+3] = 3;
            return true;
        }
    }
    if(y == prevY && (y == 1 || y == height - 3))
    {
        if(y == 1)
        {
            for(int i = 0; i <= y+1; i++)
            {
                line[i][min(prevX, x)+4] = 2;
                line[i][max(prevX, x)+4] = 2;
            }
            for(int i = min(prevX, x) + 4; i <= max(prevX, x) + 2; i++)
                lineOut[min(prevY,y)-1][i] = 2;
            lineEnd[y+1][min(prevX, x)+4] = 2;
            lineEnd[y+1][max(prevX, x)+4] = 2;
        }
        else
        {
            for(int i = y+3; i <= y+4; i++)
            {
                line[i][min(prevX, x)+4] = 2;
                line[i][max(prevX, x)+4] = 2;
            }
            for(int i = min(prevX, x) + 4; i <= max(prevX, x) + 2; i++)
                lineOut[height+1][i] = 2;
                
            lineEnd[y+3][min(prevX, x)+4] = 1;
            lineEnd[y+3][max(prevX, x)+4] = 1;
        }
        return true;
    }
    return false;  
}

bool checkL(ippxy, int idxNum[][widthB+2], int line[][widthB+2], int lineOut[][widthB+3], int lineEnd[][widthB+2])
{
    if(prevX < x)
    {
        if(prevY < y)
        {
            for(int i = min(prevY, y) + 5; i <= max(prevY, y); i += 5)  // Check ⎣
            {
                if(idxNum[i][prevX] != 300)
                    break;
                if(i == max(prevY, y))
                {
                    for(int k = min(prevX, x); k <= max(prevX, x) - 10; k += 10)
                    {
                        if(idxNum[y][k] != 300)
                            break;
                        if(k == max(prevX, x) - 10)
                        {
                            for(int j = min(prevX, x) + 5; j <= max(prevX, x) + 3; j++)
                                line[max(prevY, y)+2][j] = 2;
                            for(int j = min(prevY, y) + 3; j <= max(prevY, y) + 1; j++)
                                line[j][min(prevX, x)+4] = 2;
                            lineEnd[min(prevY, y)+3][min(prevX, x)+4] = 1;
                            lineEnd[max(prevY, y)+2][max(prevX, x)+3] = 3;
                            return true;
                        }
                    }
                }
            }

            for(int i = min(prevY, y); i <= max(prevY, y) - 5; i += 5) // Check ⎤
            {
                if(idxNum[i][x] != 300)
                    break;
                if(i == max(prevY, y) - 5)
                {
                    for(int k = min(prevX, x) + 10; k <= max(prevX, x); k += 10)
                    {
                        if(idxNum[prevY][k] != 300)
                            break;
                        if(k == max(prevX, x))
                        {
                            for(int j = min(prevX, x) + 5; j <= max(prevX, x) + 3; j++)
                                line[min(prevY, y)+2][j] = 2;
                            for(int j = min(prevY, y) + 3; j <= max(prevY, y) + 1; j++)
                                line[j][max(prevX, x)+4] = 2;
                            lineEnd[min(prevY, y)+2][min(prevX, x)+5] = 4;
                            lineEnd[max(prevY, y)+1][max(prevX, x)+4] = 2;
                            return true;
                        }
                    }
                }
            }
        }
        else
        {
            for(int i = min(prevY, y) + 5; i <= max(prevY, y); i += 5) // Check ⎦
            {
                if(idxNum[i][x] != 300)
                    break;
                if(i == max(prevY, y))
                {
                    for(int k = min(prevX, x) + 10; k <= max(prevX, x); k += 10)
                    {
                        if(idxNum[prevY][k] != 300)
                            break;
                        if(k == max(prevX, x))
                        {
                            for(int j = min(prevX, x) + 5; j <= max(prevX, x) + 3; j++)
                                line[max(prevY, y)+2][j] = 1;
                            for(int j = min(prevY, y) + 3; j <= max(prevY, y) + 1; j++)
                                line[j][max(prevX, x)+4] = 1;
                            lineEnd[max(prevY, y)+2][min(prevX, x)+5] = 4;
                            lineEnd[min(prevY, y)+3][max(prevX, x)+4] = 1;
                            return true;
                        }
                    }
                }
            }
            
            for(int i = min(prevY, y); i <= max(prevY, y) - 5; i += 5) // Check ⎡
            {
                if(idxNum[i][prevX] != 300)
                    break;
                if(i == max(prevY, y) - 5)
                {
                    for(int k = min(prevX, x); k <= max(prevX, x) - 10; k += 10)
                    {
                        if(idxNum[y][k] != 300)
                            break;
                        if(k == max(prevX, x) - 10)
                        {
                            for(int j = min(prevX, x) + 6; j <= max(prevX, x) + 3; j++)
                                line[min(prevY, y)+2][j] = 2;
                            for(int j = min(prevY, y) + 3; j <= max(prevY, y) + 1; j++)
                                line[j][min(prevX, x)+4] = 2;
                            lineEnd[min(prevY, y)+2][max(prevX, x)+3] = 3;
                            lineEnd[max(prevY, y)+1][min(prevX, x)+4] = 2;
                            return true;
                        }
                    }
                }
            }
        }
    }
    else
    {
        if(prevY < y)
        {
            for(int i = min(prevY, y); i <= max(prevY, y) - 5; i += 5) // Check ⎡
            {
                if(idxNum[i][x] != 300)
                    break;
                if(i == max(prevY, y) - 5)
                {
                    for(int k = min(prevX, x); k <= max(prevX, x) - 10; k += 10)
                    {
                        if(idxNum[prevY][k] != 300)
                            break;
                        if(k == max(prevX, x) - 10)
                        {
                            for(int j = min(prevX, x) + 6; j <= max(prevX, x) + 3; j++)
                                line[min(prevY, y)+2][j] = 2;
                            for(int j = min(prevY, y) + 3; j <= max(prevY, y) + 1; j++)
                                line[j][min(prevX, x)+4] = 2;
                            lineEnd[min(prevY, y)+2][max(prevX, x)+3] = 3;
                            lineEnd[max(prevY, y)+1][min(prevX, x)+4] = 2;
                            return true;
                        }
                    }
                }
            }

            for(int i = min(prevY, y) + 5; i <= max(prevY, y); i += 5) // Check ⎦
            {
                if(idxNum[i][prevX] != 300)
                    break;
                if(i == max(prevY, y))
                {
                    for(int k = min(prevX, x) + 10; k <= max(prevX, x); k += 10)
                    {
                        if(idxNum[y][k] != 300)
                            break;
                        if(k == max(prevX, x))
                        {
                            for(int j = min(prevX, x) + 5; j <= max(prevX, x) + 3; j++)
                                line[max(prevY, y)+2][j] = 1;
                            for(int j = min(prevY, y) + 3; j <= max(prevY, y) + 1; j++)
                                line[j][max(prevX, x)+4] = 1;
                            lineEnd[max(prevY, y)+2][min(prevX, x)+5] = 4;
                            lineEnd[min(prevY, y)+3][max(prevX, x)+4] = 1;
                            return 1;
                        }
                    }
                }
            }
        }
        else
        {
            for(int i = min(prevY, y); i <= max(prevY, y) - 5; i += 5) // Check ⎤
            {
                if(idxNum[i][prevX] != 300)
                    break;
                if(i == max(prevY, y) - 5)
                {
                    for(int k = min(prevX, x) + 10; k <= max(prevX, x); k += 10)
                    {
                        if(idxNum[y][k] != 300)
                            break;
                        if(k == max(prevX, x))
                        {
                            for(int j = min(prevX, x) + 5; j <= max(prevX, x) + 3; j++)
                                line[min(prevY, y)+2][j] = 2;
                            for(int j = min(prevY, y) + 3; j <= max(prevY, y) + 1; j++)
                                line[j][max(prevX, x)+4] = 2;
                            lineEnd[min(prevY, y)+2][min(prevX, x)+5] = 4;
                            lineEnd[max(prevY, y)+1][max(prevX, x)+4] = 2;
                            return true;
                        }
                    }
                }
            }

            for(int i = min(prevY, y) + 5; i <= max(prevY, y); i += 5) // Check ⎣
            {
                if(idxNum[i][x] != 300)
                    break;
                if(i == max(prevY, y))
                {
                    for(int k = min(prevX, x); k <= max(prevX, x) - 10; k += 10)
                    {
                        if(idxNum[prevY][k] != 300)
                            break;
                        if(k == max(prevX, x) - 10)
                        {
                            for(int j = min(prevX, x) + 5; j <= max(prevX, x) + 3; j++)
                                line[max(prevY, y)+2][j] = 2;
                            for(int j = min(prevY, y) + 3; j <= max(prevY, y) + 1; j++)
                                line[j][min(prevX, x)+4] = 2;
                            lineEnd[min(prevY, y)+3][min(prevX, x)+4] = 1;
                            lineEnd[max(prevY, y)+2][max(prevX, x)+3] = 3;
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool checkU(ippxy, int height, int width, int idxNum[][widthB+2], int line[][widthB+2], int lineOut[][widthB+3], int lineEnd[][widthB+2])
{
    int flag = 1;
    
    // Check ⊐
    if(max(prevX, x) == width - 8)
    {
        for(int i = max(prevX, x); i >= min(prevX, x) + 10; i -= 10)
        {
            if(prevX > x) // prevX là điểm có x lớn trong ảnh mô phỏng: ⎦ ⎤
            {
                if(idxNum[y][i] != 300)
                    break;
                if(i == min(prevX, x) + 10)
                {
                    for(int j = max(prevX, x) + 5; j <= width + 1; j++)
                        line[prevY+2][j] = 2;
                    for(int j = min(prevX, x) + 5; j <= width + 1; j++)
                        line[y+2][j] = 2;
                    for(int j = min(prevY, y) + 3; j <= max(prevY, y) + 1; j++)
                        lineOut[j][width+1] = 2;
                    lineEnd[y+2][min(prevX, x)+5] = 4;
                    lineEnd[prevY+2][max(prevX, x)+5] = 4;
                    return true;
                }
            }
            else // prevX là điểm có x bé trong ảnh mô phỏng: ⎤ ⎦
            {
                if(idxNum[prevY][i] != 300) 
                    break;
                if(i == min(prevX, x) + 10)
                {
                    for(int j = max(prevX, x) + 5; j <= width + 1; j++)
                        line[y+2][j] = 2;
                    for(int j = min(prevX, x) + 5; j <= width + 1; j++)
                        line[prevY+2][j] = 2;
                    for(int j = min(prevY, y) + 3; j <= max(prevY, y) + 1; j++)
                        lineOut[j][width+1] = 2;
                    lineEnd[prevY+2][min(prevX, x)+5] = 4;
                    lineEnd[y+2][max(prevX, x)+5] = 4;
                    return true;
                }                
            }
        }
    }

    for(int i = max(prevX, x) + 10; i <= width - 8; i += 10)
    {
        for(int j = min(prevY, y); j <= max(prevY, y); j += 5)
        {
            if(idxNum[j][i] != 300)
                break;
            if(j == max(prevY, y))
                flag = 0;
        }

        if(!flag || i == width - 8)
        {
            for(int j = i; j >= min(prevX, x) + 10; j -= 10)
            {
                if(prevX > x) 
                {
                    if(idxNum[y][j] != 300)
                        break;
                    if(j == min(prevX, x) + 10)
                    {
                        for(int k = i; k >= max(prevX, x) + 10; k -= 10)
                        {
                            if(idxNum[prevY][k] != 300)
                                break;
                            if(k == max(prevX, x) + 10)
                            {
                                if(flag)
                                {
                                    i += 5;
                                    for(int u = min(prevY, y) + 3; u <= max(prevY, y) + 1; u++)
                                        lineOut[u][width+1] = 2;
                                }
                                else
                                    for(int u = min(prevY, y) + 3; u <= max(prevY, y) + 1; u++)
                                        line[u][i+4] = 2;

                                for(int u = max(prevX, x) + 5; u <= i + 3; u++)
                                    line[prevY+2][u] = 2;
                                for(int u = min(prevX, x) + 5; u <= i + 3; u++)
                                    line[y+2][u] = 2;

                                lineEnd[y+2][min(prevX, x)+5] = 4;
                                lineEnd[prevY+2][max(prevX, x)+5] = 4;
                                return true;
                            }
                        }
                    }
                }
                else
                {
                    if(idxNum[prevY][j] != 300)
                        break;
                    if(j == min(prevX, x) + 10)
                    {
                        for(int k = i; k >= max(prevX, x) + 10; k -= 10)
                        {
                            if(idxNum[y][k] != 300)
                                break;
                            if(k == max(prevX, x) + 10)
                            {
                                if(flag)
                                {
                                    i += 5;
                                    for(int i = min(prevY, y) + 3; i <= max(prevY, y) + 1; i++)
                                        lineOut[i][width+1] = 2;
                                }
                                else
                                    for(int u = min(prevY, y) + 3; u <= max(prevY, y) + 1; u++)
                                        line[u][i+4] = 2;
                                for(int u = max(prevX, x) + 5; u <= i + 3; u++)
                                    line[y+2][u] = 2;
                                for(int u = min(prevX, x) + 5; u <= i + 3; u++)
                                    line[prevY+2][u] = 2;

                                lineEnd[prevY+2][min(prevX, x)+5] = 4;
                                lineEnd[y+2][max(prevX, x)+5] = 4;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    // Check ⊏
    flag = 1;
    if(min(prevX, x) == 1)
    {
        for(int i = max(prevX, x) - 10; i >= min(prevX, x); i -= 10)
        {
            if(prevX > x)
            {
                if(idxNum[prevY][i] != 300)
                    break;
                if(i == min(prevX, x))
                {
                    for(int j = max(prevX, x) + 3; j >= 0; j--)
                        line[prevY+2][j] = 2;
                    for(int j = min(prevX, x) + 3; j >= 0; j--)
                        line[y+2][j] = 2;
                    for(int j = min(prevY, y) + 3; j <= max(prevY, y) + 1; j++)
                        lineOut[j][min(prevX,x)-1] = 2;
                    lineEnd[y+2][min(prevX, x)+3] = 3;
                    lineEnd[prevY+2][max(prevX, x)+3] = 3;
                    return true;
                }
            }
            else
            {
                if(idxNum[y][i] != 300)
                    break;
                if(i == min(prevX, x))
                {
                    for(int j = max(prevX, x) + 3; j >= 0; j--)
                        line[y+2][j] = 2;
                    for(int j = min(prevX, x) + 3; j >= 0; j--)
                        line[prevY+2][j] = 2;
                    for(int j = min(prevY, y) + 3; j <= max(prevY, y) + 1; j++)
                        lineOut[j][min(prevX,x)-1] = 2;
                    lineEnd[prevY+2][min(prevX, x)+3] = 3;
                    lineEnd[y+2][max(prevX, x)+3] = 3;
                    return true;
                }                
            }
        }
    }

    for(int i = min(prevX, x) - 10; i >= 1; i -= 10)
    {
        for(int j = min(prevY, y); j <= max(prevY, y); j += 5)
        {
            if(idxNum[j][i] != 300)
                break;
            if(j == max(prevY, y))
                flag = 0;
        }

        if(!flag || i == 1)
        {
            for(int j = i; j <= min(prevX, x) - 10; j += 10)
            {
                if(prevX < x)
                {
                    if(idxNum[prevY][j] != 300)
                        break;
                    if(j == min(prevX, x) - 10)
                    {
                        for(int k = i; k <= max(prevX, x) - 10; k += 10)
                        {
                            if(idxNum[y][k] != 300)
                                break;
                            if(k == max(prevX, x) - 10)
                            {
                                if(flag)
                                {
                                    i -= 6;
                                    for(int u = min(prevY, y) + 3; u <= max(prevY, y) + 1; u++)
                                        lineOut[u][0] = 2;
                                }
                                else
                                    for(int u = min(prevY, y) + 3; u <= max(prevY, y) + 1; u++)
                                        line[u][i+4] = 2;
                                for(int u = i + 5; u <= max(prevX, x) + 3 ; u++)
                                    line[y+2][u] = 2;
                                for(int u = i + 5; u <= min(prevX, x) + 3; u++)
                                    line[prevY+2][u] = 2;

                                lineEnd[prevY+2][min(prevX, x)+3] = 3;
                                lineEnd[y+2][max(prevX, x)+3] = 3;
                                return true;
                            }
                        }
                    }
                }
                else
                {
                    if(idxNum[y][j] != 300)
                        break;
                    if(j == min(prevX, x) - 10)
                    {
                        for(int k = i; k <= max(prevX, x) - 10; k += 10)
                        {
                            if(idxNum[prevY][k] != 300)
                                break;
                            if(k == max(prevX, x) - 10)
                            {
                                if(flag)
                                {
                                    i -= 6;
                                    for(int u = min(prevY, y) + 3; u <= max(prevY, y) + 1; u++)
                                        lineOut[u][0] = 2;
                                }
                                else
                                    for(int u = min(prevY, y) + 3; u <= max(prevY, y) + 1; u++)
                                        line[u][i+4] = 2;
                                for(int u = i + 5; u <= max(prevX, x) + 3 ; u++)
                                    line[prevY+2][u] = 2;
                                for(int u = i + 5; u <= min(prevX, x) + 3; u++)
                                    line[y+2][u] = 2;

                                lineEnd[y+2][min(prevX, x)+3] = 3;
                                lineEnd[prevY+2][max(prevX, x)+3] = 3;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    //Check ⊔
    flag = 1;
    if(max(prevY, y) == height - 3)
    {
        for(int i = max(prevY, y); i >= min(prevY, y) + 5; i -= 5)
        {
            if(prevY > y)
            {
                if(idxNum[i][x] != 300)
                    break;
                if(i == min(prevY, y) + 5)
                {
                    for(int j = max(prevY, y) + 3; j <= height + 1; j++)
                        line[j][prevX+4] = 2;
                    for(int j = min(prevY, y) + 3; j <= height + 1; j++)
                        line[j][x+4] = 2;
                    for(int j = min(prevX, x) + 5; j <= max(prevX, x) + 2; j++)
                        lineOut[height+1][j] = 2;
                    lineEnd[max(prevY, y)+3][prevX+4] = 1;
                    lineEnd[min(prevY, y)+3][x+4] = 1;
                    return true;
                }
            }
            else
            {
                if(idxNum[i][prevX] != 300)
                    break;
                if(i == min(prevY, y) + 5)
                {
                    for(int j = max(prevY, y) + 3; j <= height + 1; j++)
                        line[j][x+4] = 2;
                    for(int j = min(prevY, y) + 3; j <= height + 1; j++)
                        line[j][prevX+4] = 2;
                    for(int j = min(prevX, x) + 5; j <= max(prevX, x) + 2; j++)
                        lineOut[height+1][j] = 2;
                    lineEnd[max(prevY, y)+3][x+4] = 1;
                    lineEnd[min(prevY, y)+3][prevX+4] = 1;
                    return true;
                }                
            }
        }
    }

    for(int i = max(prevY, y) + 5; i <= height - 3; i += 5)
    {
        for(int j = min(prevX, x); j <= max(prevX, x); j += 10)
        {
            if(idxNum[i][j] != 300)
                break;
            if(j == max(prevX, x))
                flag = 0;
        }

        if(!flag || i == height - 3)
        {
            for(int j = i; j >= min(prevY, y) + 5; j -= 5)
            {
                if(prevY > y)
                {
                    if(idxNum[j][x] != 300)
                        break;
                    if(j == min(prevY, y) + 5)
                    {
                        for(int k = i; k >= max(prevY, y) + 5; k -= 5)
                        {
                            if(idxNum[k][prevX] != 300)
                                break;
                            if(k == max(prevY, y) + 5)
                            {
                                if(flag)
                                {
                                    i += 3;
                                    for(int u = min(prevX, x) + 5; u <= max(prevX, x) + 2; u++)
                                        lineOut[height+1][u] = 2;
                                }
                                else
                                    for(int u = min(prevX, x) + 5; u <= max(prevX, x) + 2; u++)
                                        line[i+2][u] = 2;

                                for(int u = max(prevY, y) + 3; u <= i + 1; u++)
                                    line[u][prevX+4] = 2;
                                for(int u = min(prevY, y) + 3; u <= i + 1; u++)
                                    line[u][x+4] = 2;

                                lineEnd[max(prevY, y)+3][prevX+4] = 1;
                                lineEnd[min(prevY, y)+3][x+4] = 1;
                                return true;
                            }
                        }
                    }
                }
                else
                {
                    if(idxNum[j][prevX] != 300)
                        break;
                    if(j == min(prevY, y) + 5)
                    {
                        for(int k = i; k >= max(prevY, y) + 5; k -= 5)
                        {
                            if(idxNum[k][x] != 300)
                                break;
                            if(k == max(prevY, y) + 5)
                            {
                                if(flag)
                                {
                                    i += 3;
                                    for(int u = min(prevX, x) + 5; u <= max(prevX, x) + 2; u++)
                                        lineOut[height+1][u] = 2;
                                }
                                else
                                    for(int u = min(prevX, x) + 5; u <= max(prevX, x) + 2; u++)
                                        line[i+2][u] = 2;

                                for(int u = max(prevY, y) + 3; u <= i + 1; u++)
                                    line[u][x+4] = 2;
                                for(int u = min(prevY, y) + 3; u <= i + 1; u++)
                                    line[u][prevX+4] = 2;

                                lineEnd[max(prevY, y)+3][x+4] = 1;
                                lineEnd[min(prevY, y)+3][prevX+4] = 1;
                                return true;
                            }
                        }
                    }
                }
            }
            flag = 1;
        }
    }

    // Check ⊓
    flag = 1;
    if(min(prevY, y) == 1)
    {
        for(int i = max(prevY, y) - 5; i >= min(prevY, y); i -= 5)
        {
            if(prevY > y)
            {
                if(idxNum[i][prevX] != 300)
                    break;
                if(i == min(prevY, y))
                {
                    for(int j = max(prevY, y) + 1; j >= 0; j--)
                        line[j][prevX+4] = 2;
                    for(int j = min(prevY, y) + 1; j >= 0; j--)
                        line[j][x+4] = 2;
                    for(int j = min(prevX, x) + 5; j <= max(prevX, x) + 2; j++)
                        lineOut[min(prevY,y)-1][j] = 2;
                    lineEnd[max(prevY, y)+1][prevX+4] = 2;
                    lineEnd[min(prevY, y)+1][x+4] = 2;
                    return true;
                }
            }
            else
            {
                if(idxNum[i][x] != 300)
                    break;
                if(i == min(prevY, y))
                {
                    for(int j = max(prevY, y) + 1; j >= 0; j--)
                        line[j][x+4] = 2;
                    for(int j = min(prevY, y) + 1; j >= 0; j--)
                        line[j][prevX+4] = 2;
                    for(int j = min(prevX, x) + 5; j <= max(prevX, x) + 2; j++)
                        lineOut[min(prevY,y)-1][j] = 2;
                    lineEnd[max(prevY, y)+1][x+4] = 2;
                    lineEnd[min(prevY, y)+1][prevX+4] = 2;
                    return true;
                }                
            }
        }
    }

    for(int i = min(prevY, y) - 5; i >= 1; i -= 5)
    {
        for(int j = min(prevX, x); j <= max(prevX, x); j += 10)
        {
            if(idxNum[i][j] != 300)
                break;
            if(j == max(prevX, x))
                flag = 0;
        }

        if(!flag || i == 1)
        {
            for(int j = i; j <= min(prevY, y) - 5; j += 5)
            {
                if(prevY < y)
                {
                    if(idxNum[j][prevX] != 300)
                        break;
                    if(j == min(prevY, y) - 5)
                    {
                        for(int k = i; k <= max(prevY, y) - 5; k += 5)
                        {
                            if(idxNum[k][x] != 300)
                                break;
                            if(k == max(prevY, y) - 5)
                            {
                                if(flag)
                                {
                                    i -= 4;
                                    for(int u = min(prevX, x) + 5; u <= max(prevX, x) + 2; u++)
                                        lineOut[0][u] = 2;
                                }
                                else
                                    for(int u = min(prevX, x) + 5; u <= max(prevX, x) + 2; u++)
                                        line[i+2][u] = 2;

                                for(int u = max(prevY, y) + 1; u >= i + 3; u--)
                                    line[u][x+4] = 2;
                                for(int u = min(prevY, y) + 1; u >= i + 3; u--)
                                    line[u][prevX+4] = 2;

                                lineEnd[max(prevY, y)+1][x+4] = 2;
                                lineEnd[min(prevY, y)+1][prevX+4] = 2;
                                return true;
                            }
                        }
                    }
                }
                else
                {
                    if(idxNum[j][x] != 300)
                        break;
                    if(j == min(prevY, y) - 5)
                    {
                        for(int k = i; k <= max(prevY, y) - 5; k += 5)
                        {
                            if(idxNum[k][prevX] != 300)
                                break;
                            if(k == max(prevY, y) - 5)
                            {
                                if(flag)
                                {
                                    i -= 4;
                                    for(int u = min(prevX, x) + 5; u <= max(prevX, x) + 2; u++)
                                        lineOut[0][u] = 2;
                                }
                                else
                                    for(int u = min(prevX, x) + 5; u <= max(prevX, x) + 2; u++)
                                        line[i+2][u] = 2;

                                for(int u = max(prevY, y) + 1; u >= i + 3; u--)
                                    line[u][prevX+4] = 2;
                                for(int u = min(prevY, y) + 1; u >= i + 3; u--)
                                    line[u][x+4] = 2;

                                lineEnd[max(prevY, y)+1][prevX+4] = 2;
                                lineEnd[min(prevY, y)+1][x+4] = 2;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool checkZ(ippxy, int idxNum[][widthB+2], int line[][widthB+2], int lineOut[][widthB+3], int lineEnd[][widthB+2])
{
    int flag = 1;
    if(prevX < x)
    {
        for(int i = min(prevX, x) + 10; i <= max(prevX, x) - 10; i += 10)
        {
            for(int j = min(prevY, y); j <= max(prevY, y); j += 5)
            {
                if(idxNum[j][i] != 300)
                    break;
                if(j == max(prevY, y))
                    flag = 0;
            }
            if(!flag)
            {
                flag = 1;
                for(int j = i; j <= max(prevX, x) - 10; j += 10)
                {
                    if(idxNum[y][j] != 300)
                        break;
                    if(j == max(prevX, x) - 10)
                    {
                        for(int k = i; k >= min(prevX, x) + 10; k -= 10)
                        {
                            if(idxNum[prevY][k] != 300)
                                break;
                            if(k == min(prevX, x) + 10)
                            {
                                for(int u = min(prevY, y) + 3; u <= max(prevY, y) + 1; u++)
                                    line[u][i+4] = 2;
                                for(int u = i + 5; u <= max(prevX, x) + 3; u++)
                                    line[y+2][u] = 2;
                                for(int u = i + 3; u >= min(prevX, x) + 5; u--)
                                    line[prevY+2][u] = 2;
                                lineEnd[prevY+2][prevX+5] = 4;
                                lineEnd[y+2][x+3] = 3;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        for(int i = min(prevX, x) + 10; i <= max(prevX, x) - 10; i += 10)
        {
            for(int j = min(prevY, y); j <= max(prevY, y); j += 5)
            {
                if(idxNum[j][i] != 300)
                    break;
                if(j == max(prevY, y))
                    flag = 0;
            }
            if(!flag)
            {
                flag = 1;
                for(int j = i; j <= max(prevX, x) - 10; j += 10)
                {
                    if(idxNum[prevY][j] != 300)
                        break;
                    if(j == max(prevX, x) - 10)
                    {
                        for(int k = i; k >= min(prevX, x) + 10; k -= 10)
                        {
                            if(idxNum[y][k] != 300)
                                break;
                            if(k == min(prevX, x) + 10)
                            {
                                for(int u = min(prevY, y) + 3; u <= max(prevY, y) + 1; u++)
                                    line[u][i+4] = 2;
                                for(int u = i + 5; u <= max(prevX, x) + 3; u++)
                                    line[prevY+2][u] = 2;
                                for(int u = i + 3; u >= min(prevX, x) + 5; u--)
                                    line[y+2][u] = 2;
                                lineEnd[prevY+2][prevX+3] = 3;
                                lineEnd[y+2][x+5] = 4;
                                return true;
                            }
                        }
                    }
                }
            }
        }   
    }

    if(prevY < y)
    {
        for(int i = min(prevY, y) + 5; i <= max(prevY, y) - 5; i += 5)
        {
            for(int j = min(prevX, x); j <= max(prevX, x); j += 10)
            {
                if(idxNum[i][j] != 300)
                    break;
                if(j == max(prevX, x))
                    flag = 0;
            }
            if(!flag)
            {
                flag = 1;
                for(int j = i; j >= min(prevY, y) + 5; j -= 5)
                {
                    if(idxNum[j][prevX] != 300)
                        break;
                    if(j == min(prevY, y) + 5)
                    {
                        for(int k = i; k <= max(prevY, y) - 5; k += 5)
                        {
                            if(idxNum[k][x] != 300)
                                break;
                            if(k == max(prevY, y) - 5)
                            {
                                for(int u = min(prevX, x) + 5; u <= max(prevX, x) + 3; u++)
                                    line[i+2][u] = 2;
                                for(int u = i + 1; u >= min(prevY, y) + 3; u--)
                                    line[u][prevX+4] = 2;
                                for(int u = i + 3; u <= max(prevY, y) + 1; u++)
                                    line[u][x+4] = 2;
                                lineEnd[prevY+3][prevX+4] = 1;
                                lineEnd[y+1][x+4] = 2;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    else
    {
        for(int i = min(prevY, y) + 5; i <= max(prevY, y) - 5; i += 5)
        {
            for(int j = min(prevX, x); j <= max(prevX, x); j += 10)
            {
                if(idxNum[i][j] != 300)
                    break;
                if(j == max(prevX, x))
                    flag = 0;
            }
            if(!flag)
            {
                flag = 1;
                for(int j = i; j >= min(prevY, y) + 5; j -= 5)
                {
                    if(idxNum[j][x] != 300)
                        break;
                    if(j == min(prevY, y) + 5)
                    {
                        for(int k = i; k <= max(prevY, y) - 5; k += 5)
                        {
                            if(idxNum[k][prevX] != 300)
                                break;
                            if(k == max(prevY, y) - 5)
                            {
                                for(int u = min(prevX, x) + 5; u <= max(prevX, x) + 3; u++)
                                    line[i+2][u] = 2;
                                for(int u = i + 1; u >= min(prevY, y) + 3; u--)
                                    line[u][x+4] = 2;
                                for(int u = i + 3; u <= max(prevY, y) + 1; u++)
                                    line[u][prevX+4] = 2;
                                lineEnd[y+3][x+4] = 1;
                                lineEnd[prevY+1][prevX+4] = 2;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

// Check how to connect but not draw (For check exists 2 matching cells)
bool checkLineColEX(ippxy, int width, int idxNum[][widthB+2])
{
    int flag = 0;
    if (x == prevX)
    {
        for(int i = max(prevY, y) - 5; i >= min(prevY, y) + 5; i -= 5)
        {
            if(idxNum[i][x] != 300)
            {
                flag = 1;
                break;
            }
        }
        if(!flag)
            return true;
    }
    if(x == prevX && (x == 1 || x == width - 8))
        return true;
    return false;
}

bool checkLineRowEX(ippxy, int height, int idxNum[][widthB+2])
{
    int flag = 0;
    if (y == prevY)
    {
        for(int i = max(prevX, x) - 10; i >= min(prevX, x) + 10; i -= 10)
        {
            if(idxNum[y][i] != 300)
            {
                flag = 1;
                break;
            }
        }

        if(!flag)
            return true;
    }
    if(y == prevY && (y == 1 || y == height - 3))
        return true;
    return false;  
}

bool checkLEX(ippxy, int idxNum[][widthB+2])
{
    if(prevX < x)
    {
        if(prevY < y)
        {
            for(int i = min(prevY, y) + 5; i <= max(prevY, y); i += 5)  // Check ⎣
            {
                if(idxNum[i][prevX] != 300)
                    break;
                if(i == max(prevY, y))
                {
                    for(int k = min(prevX, x); k <= max(prevX, x) - 10; k += 10)
                    {
                        if(idxNum[y][k] != 300)
                            break;
                        if(k == max(prevX, x) - 10)
                            return true;
                    }
                }
            }

            for(int i = min(prevY, y); i <= max(prevY, y) - 5; i += 5) // Check ⎤
            {
                if(idxNum[i][x] != 300)
                    break;
                if(i == max(prevY, y) - 5)
                {
                    for(int k = min(prevX, x) + 10; k <= max(prevX, x); k += 10)
                    {
                        if(idxNum[prevY][k] != 300)
                            break;
                        if(k == max(prevX, x))
                            return true;
                    }
                }
            }
        }
        else
        {
            for(int i = min(prevY, y) + 5; i <= max(prevY, y); i += 5) // Check ⎦
            {
                if(idxNum[i][x] != 300)
                    break;
                if(i == max(prevY, y))
                {
                    for(int k = min(prevX, x) + 10; k <= max(prevX, x); k += 10)
                    {
                        if(idxNum[prevY][k] != 300)
                            break;
                        if(k == max(prevX, x))
                            return true;
                    }
                }
            }
            
            for(int i = min(prevY, y); i <= max(prevY, y) - 5; i += 5) // Check ⎡
            {
                if(idxNum[i][prevX] != 300)
                    break;
                if(i == max(prevY, y) - 5)
                {
                    for(int k = min(prevX, x); k <= max(prevX, x) - 10; k += 10)
                    {
                        if(idxNum[y][k] != 300)
                            break;
                        if(k == max(prevX, x) - 10)
                            return true;
                    }
                }
            }
        }
    }
    else
    {
        if(prevY < y)
        {
            for(int i = min(prevY, y); i <= max(prevY, y) - 5; i += 5) // Check ⎡
            {
                if(idxNum[i][x] != 300)
                    break;
                if(i == max(prevY, y) - 5)
                {
                    for(int k = min(prevX, x); k <= max(prevX, x) - 10; k += 10)
                    {
                        if(idxNum[prevY][k] != 300)
                            break;
                        if(k == max(prevX, x) - 10)
                            return true;
                    }
                }
            }

            for(int i = min(prevY, y) + 5; i <= max(prevY, y); i += 5) // Check ⎦
            {
                if(idxNum[i][prevX] != 300)
                    break;
                if(i == max(prevY, y))
                {
                    for(int k = min(prevX, x) + 10; k <= max(prevX, x); k += 10)
                    {
                        if(idxNum[y][k] != 300)
                            break;
                        if(k == max(prevX, x))
                            return true;
                    }
                }
            }
        }
        else
        {
            for(int i = min(prevY, y); i <= max(prevY, y) - 5; i += 5) // Check ⎤
            {
                if(idxNum[i][prevX] != 300)
                    break;
                if(i == max(prevY, y) - 5)
                {
                    for(int k = min(prevX, x) + 10; k <= max(prevX, x); k += 10)
                    {
                        if(idxNum[y][k] != 300)
                            break;
                        if(k == max(prevX, x))
                            return true;
                    }
                }
            }

            for(int i = min(prevY, y) + 5; i <= max(prevY, y); i += 5) // Check ⎣
            {
                if(idxNum[i][x] != 300)
                    break;
                if(i == max(prevY, y))
                {
                    for(int k = min(prevX, x); k <= max(prevX, x) - 10; k += 10)
                    {
                        if(idxNum[prevY][k] != 300)
                            break;
                        if(k == max(prevX, x) - 10)
                            return true;
                    }
                }
            }
        }
    }
    return false;
}

bool checkUEX(ippxy, int height, int width, int idxNum[][widthB+2])
{
    int flag = 1;
    
    // Check ⊐
    if(max(prevX, x) == width - 8)
    {
        for(int i = max(prevX, x); i >= min(prevX, x) + 10; i -= 10)
        {
            if(prevX > x) // prevX là điểm có x lớn trong ảnh mô phỏng: ⎦ ⎤
            {
                if(idxNum[y][i] != 300)
                    break;
                if(i == min(prevX, x) + 10)
                    return true;
            }
            else // prevX là điểm có x bé trong ảnh mô phỏng: ⎤ ⎦
            {
                if(idxNum[prevY][i] != 300) 
                    break;
                if(i == min(prevX, x) + 10)
                    return true;      
            }
        }
    }

    for(int i = max(prevX, x) + 10; i <= width - 8; i += 10)
    {
        for(int j = min(prevY, y); j <= max(prevY, y); j += 5)
        {
            if(idxNum[j][i] != 300)
                break;
            if(j == max(prevY, y))
                flag = 0;
        }

        if(!flag || i == width - 8)
        {
            for(int j = i; j >= min(prevX, x) + 10; j -= 10)
            {
                if(prevX > x) 
                {
                    if(idxNum[y][j] != 300)
                        break;
                    if(j == min(prevX, x) + 10)
                    {
                        for(int k = i; k >= max(prevX, x) + 10; k -= 10)
                        {
                            if(idxNum[prevY][k] != 300)
                                break;
                            if(k == max(prevX, x) + 10)
                                return true;
                        }
                    }
                }
                else
                {
                    if(idxNum[prevY][j] != 300)
                        break;
                    if(j == min(prevX, x) + 10)
                    {
                        for(int k = i; k >= max(prevX, x) + 10; k -= 10)
                        {
                            if(idxNum[y][k] != 300)
                                break;
                            if(k == max(prevX, x) + 10)
                                return true;
                        }
                    }
                }
            }
        }
    }

    // Check ⊏
    flag = 1;
    if(min(prevX, x) == 1)
    {
        for(int i = max(prevX, x) - 10; i >= min(prevX, x); i -= 10)
        {
            if(prevX > x)
            {
                if(idxNum[prevY][i] != 300)
                    break;
                if(i == min(prevX, x))
                    return true;
            }
            else
            {
                if(idxNum[y][i] != 300)
                    break;
                if(i == min(prevX, x))
                    return true;
            }
        }
    }

    for(int i = min(prevX, x) - 10; i >= 1; i -= 10)
    {
        for(int j = min(prevY, y); j <= max(prevY, y); j += 5)
        {
            if(idxNum[j][i] != 300)
                break;
            if(j == max(prevY, y))
                flag = 0;
        }

        if(!flag || i == 1)
        {
            for(int j = i; j <= min(prevX, x) - 10; j += 10)
            {
                if(prevX < x)
                {
                    if(idxNum[prevY][j] != 300)
                        break;
                    if(j == min(prevX, x) - 10)
                    {
                        for(int k = i; k <= max(prevX, x) - 10; k += 10)
                        {
                            if(idxNum[y][k] != 300)
                                break;
                            if(k == max(prevX, x) - 10)
                                return true;
                        }
                    }
                }
                else
                {
                    if(idxNum[y][j] != 300)
                        break;
                    if(j == min(prevX, x) - 10)
                    {
                        for(int k = i; k <= max(prevX, x) - 10; k += 10)
                        {
                            if(idxNum[prevY][k] != 300)
                                break;
                            if(k == max(prevX, x) - 10)
                                return true;
                        }
                    }
                }
            }
        }
    }

    //Check ⊔
    flag = 1;
    if(max(prevY, y) == height - 3)
    {
        for(int i = max(prevY, y); i >= min(prevY, y) + 5; i -= 5)
        {
            if(prevY > y)
            {
                if(idxNum[i][x] != 300)
                    break;
                if(i == min(prevY, y) + 5)
                    return true;
            }
            else
            {
                if(idxNum[i][prevX] != 300)
                    break;
                if(i == min(prevY, y) + 5)
                    return true;
            }
        }
    }

    for(int i = max(prevY, y) + 5; i <= height - 3; i += 5)
    {
        for(int j = min(prevX, x); j <= max(prevX, x); j += 10)
        {
            if(idxNum[i][j] != 300)
                break;
            if(j == max(prevX, x))
                flag = 0;
        }

        if(!flag || i == height - 3)
        {
            for(int j = i; j >= min(prevY, y) + 5; j -= 5)
            {
                if(prevY > y)
                {
                    if(idxNum[j][x] != 300)
                        break;
                    if(j == min(prevY, y) + 5)
                    {
                        for(int k = i; k >= max(prevY, y) + 5; k -= 5)
                        {
                            if(idxNum[k][prevX] != 300)
                                break;
                            if(k == max(prevY, y) + 5)
                                return true;
                        }
                    }
                }
                else
                {
                    if(idxNum[j][prevX] != 300)
                        break;
                    if(j == min(prevY, y) + 5)
                    {
                        for(int k = i; k >= max(prevY, y) + 5; k -= 5)
                        {
                            if(idxNum[k][x] != 300)
                                break;
                            if(k == max(prevY, y) + 5)
                                return true;
                        }
                    }
                }
            }
            flag = 1;
        }
    }

    // Check ⊓
    flag = 1;
    if(min(prevY, y) == 1)
    {
        for(int i = max(prevY, y) - 5; i >= min(prevY, y); i -= 5)
        {
            if(prevY > y)
            {
                if(idxNum[i][prevX] != 300)
                    break;
                if(i == min(prevY, y))
                    return true;
            }
            else
            {
                if(idxNum[i][x] != 300)
                    break;
                if(i == min(prevY, y))
                    return true;     
            }
        }
    }

    for(int i = min(prevY, y) - 5; i >= 1; i -= 5)
    {
        for(int j = min(prevX, x); j <= max(prevX, x); j += 10)
        {
            if(idxNum[i][j] != 300)
                break;
            if(j == max(prevX, x))
                flag = 0;
        }

        if(!flag || i == 1)
        {
            for(int j = i; j <= min(prevY, y) - 5; j += 5)
            {
                if(prevY < y)
                {
                    if(idxNum[j][prevX] != 300)
                        break;
                    if(j == min(prevY, y) - 5)
                    {
                        for(int k = i; k <= max(prevY, y) - 5; k += 5)
                        {
                            if(idxNum[k][x] != 300)
                                break;
                            if(k == max(prevY, y) - 5)
                                return true;
                        }
                    }
                }
                else
                {
                    if(idxNum[j][x] != 300)
                        break;
                    if(j == min(prevY, y) - 5)
                    {
                        for(int k = i; k <= max(prevY, y) - 5; k += 5)
                        {
                            if(idxNum[k][prevX] != 300)
                                break;
                            if(k == max(prevY, y) - 5)
                                return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool checkZEX(ippxy, int idxNum[][widthB+2])
{
    int flag = 1;
    if(prevX < x)
    {
        for(int i = min(prevX, x) + 10; i <= max(prevX, x) - 10; i += 10)
        {
            for(int j = min(prevY, y); j <= max(prevY, y); j += 5)
            {
                if(idxNum[j][i] != 300)
                    break;
                if(j == max(prevY, y))
                    flag = 0;
            }
            if(!flag)
            {
                flag = 1;
                for(int j = i; j <= max(prevX, x) - 10; j += 10)
                {
                    if(idxNum[y][j] != 300)
                        break;
                    if(j == max(prevX, x) - 10)
                    {
                        for(int k = i; k >= min(prevX, x) + 10; k -= 10)
                        {
                            if(idxNum[prevY][k] != 300)
                                break;
                            if(k == min(prevX, x) + 10)
                                return true;
                        }
                    }
                }
            }
        }
    }
    else
    {
        for(int i = min(prevX, x) + 10; i <= max(prevX, x) - 10; i += 10)
        {
            for(int j = min(prevY, y); j <= max(prevY, y); j += 5)
            {
                if(idxNum[j][i] != 300)
                    break;
                if(j == max(prevY, y))
                    flag = 0;
            }
            if(!flag)
            {
                flag = 1;
                for(int j = i; j <= max(prevX, x) - 10; j += 10)
                {
                    if(idxNum[prevY][j] != 300)
                        break;
                    if(j == max(prevX, x) - 10)
                    {
                        for(int k = i; k >= min(prevX, x) + 10; k -= 10)
                        {
                            if(idxNum[y][k] != 300)
                                break;
                            if(k == min(prevX, x) + 10)
                                return true;
                        }
                    }
                }
            }
        }   
    }

    if(prevY < y)
    {
        for(int i = min(prevY, y) + 5; i <= max(prevY, y) - 5; i += 5)
        {
            for(int j = min(prevX, x); j <= max(prevX, x); j += 10)
            {
                if(idxNum[i][j] != 300)
                    break;
                if(j == max(prevX, x))
                    flag = 0;
            }
            if(!flag)
            {
                flag = 1;
                for(int j = i; j >= min(prevY, y) + 5; j -= 5)
                {
                    if(idxNum[j][prevX] != 300)
                        break;
                    if(j == min(prevY, y) + 5)
                    {
                        for(int k = i; k <= max(prevY, y) - 5; k += 5)
                        {
                            if(idxNum[k][x] != 300)
                                break;
                            if(k == max(prevY, y) - 5)
                                return true;
                        }
                    }
                }
            }
        }
    }
    else
    {
        for(int i = min(prevY, y) + 5; i <= max(prevY, y) - 5; i += 5)
        {
            for(int j = min(prevX, x); j <= max(prevX, x); j += 10)
            {
                if(idxNum[i][j] != 300)
                    break;
                if(j == max(prevX, x))
                    flag = 0;
            }
            if(!flag)
            {
                flag = 1;
                for(int j = i; j >= min(prevY, y) + 5; j -= 5)
                {
                    if(idxNum[j][x] != 300)
                        break;
                    if(j == min(prevY, y) + 5)
                    {
                        for(int k = i; k <= max(prevY, y) - 5; k += 5)
                        {
                            if(idxNum[k][prevX] != 300)
                                break;
                            if(k == max(prevY, y) - 5)
                                return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}

// Other support và logic
bool support(iPPXY, int height, int width, int last, int obj[27], int randomObj, char idxObj[][widthB+2], int idxNum[][widthB+2], int lineHelp[][widthB+2], int line[][widthB+2], int lineOut[][widthB+3], int lineEnd[][widthB+2], int resetNum[][widthB+2], int resetLine[][widthB+2], int resetLineOut[][widthB+3], int resetLineEnd[][widthB+2])
{
    int tmpx = x, tmpy = y, tmpprevX = prevX, tmpprevY = prevY;
    for(int i = 1; i <= height - 3; i += 5)
    {
        for(int j = 1; j <= width - 8; j += 10)
        {
            for(int u = i; u <= height - 3; u += 5)
            {
                for(int v = j + 10; v <= width - 8; v += 10)
                {
                    if(idxNum[i][j] == idxNum[u][v] && idxNum[u][v] != 300)
                    {
                        prevX = j;
                        prevY = i;
                        x = v;
                        y = u;
                        if(checkLineCol(ppxy, width, idxNum, line, lineOut, lineEnd) || checkLineRow(ppxy, height, idxNum, line, lineOut, lineEnd) || checkL(ppxy, idxNum, line, lineOut, lineEnd) || checkU(ppxy, height, width, idxNum, line, lineOut, lineEnd) || checkZ(ppxy, idxNum, line, lineOut, lineEnd))
                        {
                            for(int k = prevX; k <= prevX + 8; k++)
                            {
                                lineHelp[prevY-1][k] = 2;
                                lineHelp[prevY+4][k] = 2;
                            }
                            for(int k = prevY; k <= prevY + 3; k++)
                            {
                                lineHelp[k][prevX-1] = 2;
                                lineHelp[k][prevX+9] = 2;
                            }

                            for(int k = x; k <= x + 8; k++)
                            {
                                lineHelp[y-1][k] = 2;
                                lineHelp[y+4][k] = 2;
                            }
                            for(int k = y; k <= y + 3; k++)
                            {
                                lineHelp[k][x-1] = 2;
                                lineHelp[k][x+9] = 2;
                            }

                            prevX = tmpprevX;
                            prevY = tmpprevY;
                            x = tmpx;
                            y = tmpy;
                            return true;
                        }
                    }
                }
            }
        }
    }
    prevX = 200;
    prevY = 200;
    x = tmpx;
    y = tmpy;
    From(height, width, idxNum, line, lineOut, lineEnd, resetNum, resetLine, resetLineOut, resetLineEnd);
    change(height, width, last, obj, randomObj, idxObj, idxNum, line, lineOut, lineEnd, resetNum, resetLine, resetLineOut, resetLineEnd);
    To(height, width, idxNum, line, lineOut, lineEnd, resetNum, resetLine, resetLineOut, resetLineEnd);
    return false;
}

// Check if there are any matching boxes
bool noExpired(ippxy, int height, int width, int last, int obj[27], int randomObj, char idxObj[][widthB+2], int idxNum[][widthB+2], int lineHelp[][widthB+2], int line[][widthB+2], int lineOut[][widthB+3], int lineEnd[][widthB+2], int resetNum[][widthB+2], int resetLine[][widthB+2], int resetLineOut[][widthB+3], int resetLineEnd[][widthB+2])
{
    int tmpx = x, tmpy = y;
    for(int i = 1; i <= height - 3; i += 5)
    {
        for(int j = 1; j <= width - 8; j += 10)
        {
            for(int u = i; u <= height - 3; u += 5)
            {
                for(int v = j + 10; v <= width - 8; v += 10)
                {
                    if(idxNum[i][j] == idxNum[u][v] && idxNum[u][v] != 300)
                    {
                        prevX = j;
                        prevY = i;
                        x = v;
                        y = u;
                        if(checkLineColEX(ppxy, width, idxNum) || checkLineRowEX(ppxy, height, idxNum) || checkLEX(ppxy, idxNum) || checkUEX(ppxy, height, width, idxNum) || checkZEX(ppxy, idxNum))
                        {
                            prevX = 200;
                            prevY = 200;
                            x = tmpx;
                            y = tmpy;
                            return true;
                        }
                    }
                }
            }
        }
    }
    prevX = 200;
    prevY = 200;
    x = tmpx;
    y = tmpy;
    return false;
}

// Delete 2 boxes
void del(iPPXY, int height, int width, int &last, int &score, bool &endGame, int obj[27], int randomObj, char idxObj[][widthB+2],int idxNum[][widthB+2], int line[][widthB+2], int lineOut[][widthB+3], int lineEnd[][widthB+2], int lineHelp[][widthB+2], int resetNum[][widthB+2], int resetLine[][widthB+2], int resetLineOut[][widthB+3], int resetLineEnd[][widthB+2], int greenBlock[][widthB+2], bool &soundDele)
{
    // Tô màu greenBlock
    for(int i=prevY; i<=prevY+4; i++)
        for(int j=prevX; j<=prevX+9; j++)
            if(line[i][j] == 0)
                greenBlock[i][j] = 1;

    for(int i=y; i<=y+4; i++)
        for(int j=x; j<=x+9; j++)
            if(line[i][j] == 0)
                greenBlock[i][j] = 1;

    // Xoá ô
    for(int i=prevY; i<=prevY+3; i++)
        for(int j=prevX; j<=prevX+8; j++)
            idxNum[i][j] = 300;
    for(int i=y; i<=y+3; i++)
        for(int j=x; j<=x+8; j++)
            idxNum[i][j] = 300;

    for(int i=prevX; i<=prevX+8; i++) 
    {
        idxNum[prevY-1][i]--; // Đường biên trên
        idxNum[prevY+4][i]--; // Đường biên dưới
    }
    for(int i=prevY; i<=prevY+3; i++) 
    {
        idxNum[i][prevX-1]--; // Đường biên trái
        idxNum[i][prevX+9]--; // Đường biên phải
    }

    for(int i=x; i<=x+8; i++)
    {
        idxNum[y-1][i]--; // Đường biên trên
        idxNum[y+4][i]--; // Đường biên dưới
    }
    for(int i=y; i<=y+3; i++) 
    {
        idxNum[i][x-1]--; // Đường biên trái
        idxNum[i][x+9]--; // Đường biên phải
    }
    // âm thanh
    soundDele = true;

    score += 10;
    last--;
    prevX = 200;
    prevY = 200;

    if(last > 1)
        if(!noExpired(ppxy, height, width, last, obj, randomObj, idxObj, idxNum, lineHelp, line, lineOut, lineEnd, resetNum, resetLine, resetLineOut, resetLineEnd))
        {
            From(height, width, idxNum, line, lineOut, lineEnd, resetNum, resetLine, resetLineOut, resetLineEnd);
            change(height, width, last, obj, randomObj, idxObj, idxNum, line, lineOut, lineEnd, resetNum, resetLine, resetLineOut, resetLineEnd);
            To(height, width, idxNum, line, lineOut, lineEnd, resetNum, resetLine, resetLineOut, resetLineEnd);
        }
}

// Movement navigation and in-game functions
void logic(iPPXY, int height, int width, int &dir, int &last, int &score, bool &endPause, bool &endGame, bool &endMap, bool &confirm, int obj[27], int randomObj, char idxObj[][widthB+2],int idxNum[][widthB+2], int line[][widthB+2], int lineOut[][widthB+3], int lineEnd[][widthB+2], int lineHelp[][widthB+2], int resetNum[][widthB+2], int resetLine[][widthB+2], int resetLineOut[][widthB+3], int resetLineEnd[][widthB+2], int greenBlock[][widthB+2], int redBlock[][widthB+2], bool &soundDele, bool &soundErr, bool &soundFi)
{
    switch(dir)
	{
        // Left shift
		case 1:
		{   
            if(x == 1)
                x = width - 8;
            else
                x -= 10;
			break;
        }
        // Right shift
		case 2:
		{
            if(x == width - 8)
                x = 1;
            else
                x += 10;
			break;
        }
        // Up shift
		case 3:
		{
            if(y == 1)
                y = height - 3;
            else
                y -= 5;
            break;
        }
        // Down shift
		case 4:
		{
            if(y == height - 3)
                y = 1;
            else
                y += 5;
            break;
        }     
        // Using reset function
        case 6:
        {
            prevX = 200;
            prevY = 200;
            if(score != 0)
                score -= 5;
            From(height, width, idxNum, line, lineOut, lineEnd, resetNum, resetLine, resetLineOut, resetLineEnd);
            change(height, width, last, obj, randomObj, idxObj, idxNum, line, lineOut, lineEnd, resetNum, resetLine, resetLineOut, resetLineEnd);
            To(height, width, idxNum, line, lineOut, lineEnd, resetNum, resetLine, resetLineOut, resetLineEnd);
            break;
        }
        // Using help function
        case 7:
        {
            support(ppxy, height, width, last, obj, randomObj, idxObj, idxNum, lineHelp, line, lineOut, lineEnd, resetNum, resetLine, resetLineOut, resetLineEnd);
            if(score != 0)
                score -= 5;
            break;
        }
        // Confirm exit the game if out of boxes
        case 8:
            if(last == 0)
            {
                endGame = true;
                endMap = false;
            }
            break;
        // Using pause function
        case 9:
            endPause = false;
        // Confirm choosing box
        case 5:
        {
            // Confirm continue when the box runs out
            if(last == 0)
            {
                endGame = true;
                confirm = true;
                soundFi = true;
            }
            // Select the first box
            else if((prevX == 200 && prevY == 200) && idxNum[y][x] != 300)
            {
                prevX = x;
                prevY = y;
            }
            // Unselect box
            else if(prevX == x && prevY == y)
            {
                prevX = 200;
                prevY = 200;
            }
            // Check if 2 cells satisfy the deletion condition
            else if(idxNum[prevY][prevX] == idxNum[y][x] && idxNum[y][x] != 300)
            {  
                if(checkLineCol(ppxy, width, idxNum, line, lineOut, lineEnd))
                    del(ppxy, height, width, last, score, endGame, obj, randomObj, idxObj, idxNum, line, lineOut, lineEnd, lineHelp, resetNum, resetLine, resetLineOut, resetLineEnd, greenBlock, soundDele);
                else if(checkLineRow(ppxy, height, idxNum, line, lineOut, lineEnd))
                    del(ppxy, height, width, last, score, endGame, obj, randomObj, idxObj, idxNum, line, lineOut, lineEnd, lineHelp, resetNum, resetLine, resetLineOut, resetLineEnd, greenBlock, soundDele);
                else if(checkL(ppxy, idxNum, line, lineOut, lineEnd))
                    del(ppxy, height, width, last, score, endGame, obj, randomObj, idxObj, idxNum, line, lineOut, lineEnd, lineHelp, resetNum, resetLine, resetLineOut, resetLineEnd, greenBlock, soundDele);
                else if(checkU(ppxy, height, width, idxNum, line, lineOut, lineEnd))
                    del(ppxy, height, width, last, score, endGame, obj, randomObj, idxObj, idxNum, line, lineOut, lineEnd, lineHelp, resetNum, resetLine, resetLineOut, resetLineEnd, greenBlock, soundDele);
                else if(checkZ(ppxy, idxNum, line, lineOut, lineEnd))
                    del(ppxy, height, width, last, score, endGame, obj, randomObj, idxObj, idxNum, line, lineOut, lineEnd, lineHelp, resetNum, resetLine, resetLineOut, resetLineEnd, greenBlock, soundDele);
                // Can't delete
                else
                {
                    for(int i=prevY; i<=prevY+4; i++)
                        for(int j=prevX; j<=prevX+9; j++)
                        {
                            if(i%5 == 3 && j%5 == 0 && j%10 != 0)
                                continue;
                            if(line[i][j] == 0)
                                redBlock[i][j] = 2;
                        }
                    for(int i=y; i<=y+4; i++)
                        for(int j=x; j<=x+9; j++)
                        {
                            if(i%5 == 3 && j%5 == 0 && j%10 != 0)
                                continue;
                            if(line[i][j] == 0)
                                redBlock[i][j] = 2;
                        }
                    // The boxes can't be deleted
                    soundErr = true;
                }
            }
            // The selected boxes don't have the same letter. Meaning can't be deleted
            else if(idxNum[y][x] != 300)
            {
                for(int i=prevY; i<=prevY+4; i++)
                    for(int j=prevX; j<=prevX+9; j++)
                    {
                        if(i%5 == 3 && j%5 == 0 && j%10 != 0)
                            continue;
                        if(line[i][j] == 0)
                            redBlock[i][j] = 2;
                    }
                for(int i=y; i<=y+4; i++)
                    for(int j=x; j<=x+9; j++)
                    {
                        if(i%5 == 3 && j%5 == 0 && j%10 != 0)
                            continue;
                        if(line[i][j] == 0)
                            redBlock[i][j] = 2;
                    }
                // The boxes can't be deleted
                soundErr = true;
            }
            break;
        }
		default:
            break;
	}
    dir = 0;
}

// Reset all variables
void reset(char idxObj[][widthB+2], int idxNum[][widthB+2], int line[][widthB+2], int lineOut[][widthB+3], int lineEnd[][widthB+2], int lineHelp[][widthB+2], int resetNum[][widthB+2], int resetLine[][widthB+2], int resetLineOut[][widthB+3], int resetLineEnd[][widthB+2])
{
    for(int i = 0; i < heightB + 2; i++)
    {
        for(int j = 0; j < widthB + 2; j++)
        {
            idxNum[i][j] = 0;

            line[i][j] = 0;
            lineOut[i][j] = 0;
            lineEnd[i][j] = 0;

            resetNum[i][j] = 0;
            resetLine[i][j] = 0;
            resetLineOut[i][j] = 0;
            resetLineEnd[i][j] = 0;

            idxObj[i][j] = '\0';
        }
    }
}
