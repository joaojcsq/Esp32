import serial
import serial.tools.list_ports
while True:
    print("ESP32 conectado? y/n")
    value = input()
    if value == "y":
        esp_ports = [
            p.device
            for p in serial.tools.list_ports.comports()
            if 'Silicon' in p.description  # isso pode mudar com novos ESPs
        ]

        try:
            print("")
            print("#"*30)
            print(f"ESP32 encontrado na porta -->", esp_ports[0])
            print("#"*30)
            print("")
            print("Nova pesquisa? y/n")
            value1 = input()
            if value1 == "n":
                break
            else:
                print("")
        except IndexError:
            print("ESP32 não encontrado!!!")
            print("#"*30)
            print("")
    else:
        print("Por favor, conecte!")
        print("")