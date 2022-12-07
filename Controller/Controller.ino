#include "0-Params.hpp"
#include "1-Core.hpp"
#include "2-Serial.hpp"

SerialHandler USB;
ControllerCore Core;

void setup() {                            // Esta é a rotina padrão que é executada quando o Arduino é reinicializado, é OBRIGATÓRIA.
  USB.init();                             // Chama a função que inicia a porta serial para transmissão de dados.
  Core.init();
  USB.serialWelcome();                    // Se a porta estiver habilitada, ela envia o menu de configuração para o console serial.
}

void loop() {                             // Terminada a rotina "setup()", o "loop()" é executado indefinidamente até que o Arduino seja desligado.
  if (USB.available()){
    USB.serialWatchDog();                 // Rotina que verifica se algo foi enviado para a porta serial.
    Core.updateSerial(USB);               // Se uma solicitação para alterar um parâmetro foi enviada, atualize-a e salve-a no cartão SD.
  }
  Core.updateStatus();                    // Dependendo do estado do botão Auto/Manual, ele executa a função principal de forma diferente.
  delay(LOOP_DELAY);                      // Uma pausa de milissegundos DELAY_LOOP para que não faça muitos loops e use menos energia.
}
