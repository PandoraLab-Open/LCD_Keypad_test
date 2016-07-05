/*************************************************************************************
  DESCRIÇÃO:
  Teste do LCD Keypad Shield v 1.0 e função reaproveitável para leitura dos botões

  POR:
  PandoraLab
  www.pandoralab.com.br

  COLABORADORES:
  Mau Jabur - maumaker at pandoralab dot com dot br

  HARDWARE:
  Arduino Uno
  https://pandoralab.com.br/loja/arduino-uno-r3-smd/

  https://pandoralab.com.br/loja/display-lcd-16x2-com-mini-teclado/

  TOOLCHAIN:
  Arduino IDE 1.6.7

  BIBLIOTECAS UTILIZADAS:
  NewLiquidCrystal 1.3.4 - https://bitbucket.org/fmalpartida/new-liquidcrystal
  (pode funcionar com outras bibliotecas)

  LICENÇA:
  Attribution-ShareAlike 4.0 International (CC BY-SA 4.0)
  http://creativecommons.org/licenses/by-sa/4.0/

  Você livremente pode:
  Compartilhar - copiar e redistribuir o material em qualquer meio ou formato
  Adaptar - Remixar, transformar e basear-se no material para qualquer proposito,
  até mesmo comercialmente
  A licenciante não pode revogar estas liberdades enquanto você seguir os termos
  da licença

  Atribuição - Você deve dar crédito apropriado, fronecer um link para a licença e indicar se
  mudanças foram feitas. Você pode fazer isto de forma razoável, mas não de forma a
  sugerir que o licenciante apoia você ou seu uso.

  ShareAlike - (Compartilhe da mesma forma) Se você remixar, transformar ou basear-se
  no material você deve distribuir suas contribuições com a mesma licença que a
  original

  Sem restrições adicionais - Voce não pode aplicar termos legais ou medidas
  tecnológicas que legalmente restrinjam outros de fazer qualquer coisa que a licença
  permita.

  You are free to:
  Share — copy and redistribute the material in any medium or format
  Adapt — remix, transform, and build upon the material
  for any purpose, even commercially.
  The licensor cannot revoke these freedoms as long as you follow the license terms.

  Attribution — You must give appropriate credit, provide a link to the license, and
  indicate if changes were made. You may do so in any reasonable manner, but not in
  any way that suggests the licensor endorses you or your use.

  ShareAlike — If you remix, transform, or build upon the material, you must
  distribute your contributions under the same license as the original.

  No additional restrictions — You may not apply legal terms or technological measures
  that legally restrict others from doing anything the license permits.
 **************************************************************************************/

/*************************************************************************************
  based on code by
  Mark Bramwell, July 2010

  http://www.dfrobot.com/wiki/index.php/LCD_KeyPad_Shield_For_Arduino_SKU:_DFR0009

  Connection: Plug the LCD Keypad to the UNO(or other controllers)

**************************************************************************************/

#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 4, 5, 6, 7); // pinos usados pelo display

// PARA REAPROVEITAR A FUNÇÃO, COPIE COMEÇANDO AQUI

// constantes com nome, para facilitar a leitura do código
#define btNENHUM   0
#define btSELECT   1
#define btESQUERDA 2
#define btACIMA    3
#define btABAIXO   4
#define btDIREITA  5

#define btPORTA A0

#define SHIELD_VERSION 1.0

// le botão pressionado no instante
int le_botoes() {
  int adc_key_in = analogRead(btPORTA);  // lê o valor da entrada analógica

  // OS meus botões retornam os valores 0, 98, 254, 409 e 639
  // os valores abaixo definem faixas que contem estes valores
  // e vieram do codigo original em inglês

  // Verificamos o valor para "nenhum botão pressionado" primeiro
  // pois deve ser o caso mais frequente
  if (adc_key_in > 850) return btNENHUM;

  // para versão 1.0 do shield
  if (adc_key_in < 50)   return btDIREITA;
  if (adc_key_in < 195)  return btACIMA;
  if (adc_key_in < 380)  return btABAIXO;
  if (adc_key_in < 555)  return btESQUERDA;
  if (adc_key_in < 790)  return btSELECT;

  // Para versão 1.1 do shield
  /*
      if (adc_key_in < 50)   return btDIREITA;
      if (adc_key_in < 250)  return btACIMA;
      if (adc_key_in < 450)  return btABAIXO;
      if (adc_key_in < 650)  return btESQUERDA;
      if (adc_key_in < 850)  return btSELECT;
    /**/

  return btNENHUM; // se nenhum botão foi detectado
}

// PARA REAPROVEITAR A FUNÇÃO, COPIE ATÉ AQUI

int botao_lido;

void setup() {
  lcd.begin(16, 2); // inicializa o display com 16 colunas e duas linhas

  lcd.home(); // começa a escrever no topo do display
  lcd.print("aperte qualquer"); // print a simple message on the LCD
  lcd.setCursor(0, 1); // começo da segunda linha
  lcd.print("tecla p/ inicio");

  // exemplo de como aguardar "qualquer tecla"
  do { // do = faça
    botao_lido = le_botoes(); // leia os botoes
  } while (botao_lido == btNENHUM); // repita enquanto botao_lido for nenhum


  // após apertado, continua o programa
  lcd.clear();

  lcd.home(); // começa a escrever no topo do display
  lcd.print("TESTE DE BOTOES"); // mensagem para o display
}

void loop() {
  lcd.setCursor(0, 1); // começo da segunda linha
  botao_lido = le_botoes(); // read the buttons

  switch (botao_lido) { // dependendo de qual botão foi lido, faz uma ação

    case btDIREITA: {
        lcd.print("DIREITA  ");
        break;
      }
    case btESQUERDA: {
        lcd.print("ESQUERDA ");
        break;
      }
    case btACIMA: {
        lcd.print("ACIMA    ");
        break;
      }
    case btABAIXO: {
        lcd.print("ABAIXO   ");
        break;
      }
    case btSELECT: {
        lcd.print("SELECT   ");
        break;
      }
    case btNENHUM: {
        lcd.print("NENHUM   ");
        break;
      }
  }

  lcd.print("V: ");
  lcd.print(analogRead(btPORTA)); // valor 
  lcd.print("   ");

  delay(250);
}
