unsigned char Display_Dat[4736];//全屏像素点（296*128)/8=4736

/********************************************************************************************************
* 函数: Fresh_Full_Dat()
* 描述: 刷新全屏图像数据
* 参数 :x-显示图像X轴
* 参数 :y-显示图像Y轴
* 参数 :dat[]-图像数据
* 参数 pix_x-图像长度
* 参数 pix_y-图像宽度
* 返回值:none
********************************************************************************************************/
void Fresh_Full_Dat(uint16_t x,uint16_t y,uint8_t pix_dat[],uint16_t pix_x,uint16_t pix_y)
{
	uint8_t dot_count;
	uint16_t i;
	uint16_t j;
	uint16_t dot = pix_x*pix_y/8;
  
	j = 0;
	dot_count = 0;
	//x轴偏移量和Y轴偏移量
	i = x*16 + y/8;

	for(; i < 4736; i++)
	{
		Display_Dat[i] = pix_dat[j];
		j++;
		dot_count++;
		if(dot_count >= pix_y/8)//换列
		{
			dot_count = 0;
			while(1)//x轴前进1个像素点
			{
				if(i%16 == 0)
					break;
				else
					i++;
			}
			i = i + y/8 - 1;	
		}
		if(j >= dot)//图像最后一个像素点
			break;
	}	
}

/********************************************************************************************************
* 函数: EPD_Full_Display()
* 描述: 显示全屏数据
* 参数 :*datas-全屏图像数据
* 返回值:none
********************************************************************************************************/
void EPD_Full_Display( const unsigned char * datas)
{
	unsigned int i;   
	
  EPD_W29_WriteCMD(0x24);   //Write Black and White image to RAM
	EPD_W29_CS_1;
	EPD_W29_CS_0;
	EPD_W29_DC_1;  // D/C#   0:command  1:data
	
	for(i=0;i<4736;i++)
	{               
		SPI_Write(*datas);
		datas++;
	} 
	EPD_W29_CS_1;		 
	 
	EPD_W29_Update();
}
