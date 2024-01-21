#define ALIGN_CENTER(t)                 ((72 - (u8g2.getUTF8Width(t))) / 2)
#define ALIGN_END(t)                    (72 - (u8g2.getUTF8Width(t)))

#define utf8_bytes_per_char 4  // Assuming each Unicode character is encoded with 3 bytes

// Display
static void init_display(void) {
  Wire.begin(SDA_PIN, SCL_PIN);
  u8g2.begin();
}

void draw_prepare(void) {
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}

void draw_volume_icon(u8g2_uint_t x = 37, u8g2_uint_t y = 2) {
  const uint32_t unicode_code[5] = {0xe04f, 0xe04e, 0xe050, 0xe05d, 0xe203};
  char utf8_sequence[utf8_bytes_per_char];
  int vol = get_buzzer_volume();
  int vol_icon = 4;
  if(vol == 0) { vol_icon = 0; }
  else if(vol == 1) { vol_icon = 1; }
  else if(vol <=  10) { vol_icon = 2; }
  else if(vol <= 25) { vol_icon = 3; }

  u8g2.setFont(u8g2_font_siji_t_6x10);
  encode_unicode_to_UTF8(unicode_code[vol_icon], utf8_sequence);

  u8g2.drawUTF8(x, y, utf8_sequence);
}

void encode_unicode_to_UTF8(uint32_t unicode_code, char utf8_sequence[]) {             
  utf8_sequence[0] = 0xE0 | (unicode_code >> 12);
  utf8_sequence[1] = 0x80 | ((unicode_code >> 6) & 0x3F);
  utf8_sequence[2] = 0x80 | (unicode_code & 0x3F);
  utf8_sequence[utf8_bytes_per_char] = '\0';  // Null-terminate the string
}

void draw_bat(u8g2_uint_t x = 72-19, u8g2_uint_t y = 1) {
  int w = 18;
  int h = 10; 
  int r = 1; 
  int offset = 2;
  int bat_width = (bat_value * (w - 2*offset))/100;
  #ifdef DEBUG_BAT
    char bat_mv[5];
    sprintf(bat_mv, "%d%", bat_value);
    u8g2.drawStr(ALIGN_END(bat_mv), y, bat_mv);
  #else

    u8g2.drawRFrame(x, y, w, h, r);
    u8g2.drawBox(x + w, y + offset, 1, h-2*offset);

    u8g2.drawBox(x + offset, y + offset, bat_width, h-2*offset);
  #endif
}

void draw_score(u8g2_uint_t x, u8g2_uint_t y, bool is_centered) {
  char score[10];
  sprintf(score, "%d-%d", goals_home, goals_away);

  int x_pos = is_centered ? ALIGN_CENTER(score) : x;
  u8g2.drawStr(x_pos, y, score);
}

void draw_time(u8g2_uint_t x, u8g2_uint_t y, bool is_centered) {
  int minutes = countdown_main / 60;
  int seconds = countdown_main % 60;
  char time_string[10];
  sprintf(time_string, "%01d:%02d", minutes, seconds);

  int x_pos = is_centered ? ALIGN_CENTER(time_string) : x;
  u8g2.drawStr(x_pos, y, time_string);
}

void draw_sub(u8g2_uint_t x = 0, u8g2_uint_t y = 0) {
  u8g2.setFont(u8g2_font_freedoomr10_tu);
  switch(mode) {
    case MAIN_TIMER:
      draw_score(x, y, false);
      break;
    case MAIN_SCORE:
      draw_time(x, y, false);
      break;
  }
}

void draw_main(u8g2_uint_t x = 0, u8g2_uint_t y = 15) {
  switch(mode) {
    case MAIN_TIMER:
      u8g2.setFont(u8g2_font_freedoomr25_tn);
      draw_time(x, y, true);
      break;
    case MAIN_SCORE:
      u8g2.setFont(u8g2_font_logisoso20_tn);
      draw_score(x, y, true);
      break;
  }
}

void draw(void) {
  u8g2.clearBuffer();
  draw_prepare();

  draw_main();
  draw_sub();
  draw_volume_icon();
  draw_bat();

  u8g2.sendBuffer();
}