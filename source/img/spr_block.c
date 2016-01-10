/* GIMP RGBA C-Source image dump (spr_block.c) */

static const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel; /* 2:RGB16, 3:RGB, 4:RGBA */ 
  unsigned char	 pixel_data[16 * 16 * 4 + 1];
} spr_block = {
  16, 16, 4,
  "RO!\374OJ\40\372LJ\36\371%&\24\374NR#\375GJ\37\37668\35\373VZ$\371[`$\374"
  "35\27\367KP\36\371cl&\372PU\36\356((\23\323cf!\312XY\40\303OI\37\372`y.\364"
  "Ti'\351Ti$\361L`!\370I\\\40\356Zo)\355\\s'\357j\203,\367o\212.\350\177\235"
  "3\360\200\236:\355\200\2379\344\212\2527\313}\2351\234PO\35\302@;\31\373"
  "Th'\360Oa\"\350ET\35\344FW\36\351DU\34\344L]\37\347N_\37\346Ui#\347^t%\344"
  "p\212.\352f~,\341t\2171\325v\222/\267n\211*\231KI\33\307?9\34\373Th\"\366"
  "HZ\37\352BS\34\350>M\33\343@N\31\343CS\31\345DT\30\345J[\33\350Zp\"\347Y"
  "n$\344\\r%\332h\202+\304b{&\256d\177%\241EE\37\316G?\32\370HZ#\354AQ\35\351"
  "9G\27\3449G\26\344<J\26\344@N\25\343AQ\24\350L^\32\353Sf\36\353GX\33\342"
  "Rh\37\317Si\40\306Vm\40\273b|&\244IH\33\324A:\31\371FW\"\3568F\32\3515B\26"
  "\3457C\22\343:H\21\343=L\21\344AP\25\350DV\27\355<K\24\352@Q\26\332?P\26"
  "\330Nb\35\312Si\36\271_w&\252HF\33\3310*\30\370>N\35\3530>\23\3473@\23\344"
  "5B\17\3439G\16\345?N\22\344?M\26\351<J\24\3527E\20\3404B\20\340<M\24\330"
  "G[\31\311Sh\35\265Xn#\27555\31\334G=\33\370<M\31\3478F\26\3445B\22\3438F"
  "\20\344<J\20\346?N\22\345<J\23\3516D\20\3431>\15\3512>\20\3468G\24\344CV"
  "\30\314L_\34\311M`\37\315JI\34\335D;\32\366FX\36\344;J\26\3437D\21\346;I"
  "\22\346?M\20\357<K\20\3508F\22\3457D\20\354,7\14\3533?\20\3478F\23\340@Q"
  "\25\326BR\31\332Nb\37\313EE\33\337+&\23\367Qf!\341<K\27\3436D\20\351>L\23"
  "\347?N\22\3549G\17\3519G\21\3558E\22\360+6\16\3610=\17\3465D\21\337;I\25"
  "\342GX\32\333Qe\"\315,+\27\35293\26\354Sh%\344@N\31\342:I\22\343=L\23\353"
  "<K\22\3573@\15\362?M\25\360=K\25\364-9\16\3575B\20\343>N\26\342FW\33\345"
  "L^\34\334K^!\336QS\"\367KD\35\342Vl(\332BQ\33\3424A\20\3424A\20\3512>\16"
  "\3708E\22\366?M\27\3606C\23\3561=\17\3546C\22\345?N\27\353HX\34\351J]\37"
  "\347J\\$\361CC\35\372=<\31\335Rg'\340BR\35\3368F\30\3373?\24\3476C\25\367"
  "=L\27\363BR\30\364>L\26\3579H\24\3548F\25\354CS\33\352HY\37\352IZ\"\356L"
  "_&\36789\27\374\"!\24\324ax/\344O`&\3512>\26\337<J\26\353DU\33\356DU\32\352"
  "GX\33\353IZ\37\357CR\33\362:H\27\361>M\33\351GY\"\346L^%\351Ma&\354FF#\365"
  "PN\"\333Ud*\351AL\36\351BN\34\347ER\32\346JX\36\345IY!\355Q^&\361DO\40\355"
  "7B\32\344JV!\337FS\40\351FU!\366Ve*\371Pb'\373GJ\37\373DB\34\273RO\"\354"
  "KM\37\374@D\40\376GJ\35\367HJ\36\36755\33\362HI\37\374=<\32\371'&\25\367"
  "IG\37\361AA\34\364:;\30\374JM%\373IL\40\372JL\40\364",
};
