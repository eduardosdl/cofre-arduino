# Cofre Arduino com Senha

Este projeto Arduino implementa um cofre seguro controlado por senha utilizando um teclado matricial, um servo motor para travar/destravar o cofre, um sensor de força, um piezo para alarme e um display LCD para exibir informações.

## Descrição do Projeto

O cofre Arduino com senha funciona da seguinte maneira:

1. **Teclado Matricial**: Utilizado para inserir a senha. O teclado possui 4 linhas e 4 colunas, com teclas numeradas de '0' a '9' e teclas funcionais 'A', 'B', 'C' e 'D'.
2. **Servo Motor**: Controla a trava do cofre. Quando a senha correta é inserida, o servo gira para destravar o cofre.
3. **Display LCD**: Utilizado para exibir a senha inserida e instruções para o usuário.
4. **Sensor de Força**: Detecta tentativas de arrombamento. Se o sensor detectar uma força abaixo de um determinado limiar, o alarme é ativado.
5. **Piezo**: Emite um som de alarme se uma tentativa incorreta de entrada for detectada ou se o sensor de força for acionado.

## Funcionalidades

- **Inserção de Senha**: O usuário pode inserir uma senha de 4 dígitos utilizando o teclado matricial.
- **Verificação de Senha**: Pressionar a tecla 'C' verifica se a senha inserida está correta.
- **Alteração de Senha**: Quando o cofre está aberto, o usuário pode alterar a senha pressionando a tecla 'A'.
- **Fechamento do Cofre**: Pressionar a tecla 'B' fecha o cofre quando ele está aberto.
- **Alarme**: Um alarme é acionado se o sensor de força detectar uma tentativa de arrombamento ou se mais de três tentativas de senha incorretas forem feitas.

## Espaço para Foto

![Foto do Projeto no TinkerCad](https://github.com/eduardosdl/cofre-arduino/blob/main/digrama-tinkercad.png)

## Como Usar

Para utilizar o cofre Arduino com senha, siga estas instruções:

1. **Inserir Senha**: Utilize o teclado para inserir uma senha de 4 dígitos.
2. **Verificar Senha**: Pressione a tecla 'C' para verificar se a senha está correta. Se estiver correta, o servo motor destravará o cofre.
3. **Alterar Senha**: Quando o cofre estiver aberto, pressione a tecla 'A' para alterar a senha.
4. **Fechar Cofre**: Pressione a tecla 'B' para fechar o cofre.
5. **Ativar Alarme**: O alarme será ativado automaticamente se uma tentativa de arrombamento for detectada ou se mais de três tentativas de senha incorretas forem feitas.

## Contribuições

Sinta-se à vontade para abrir issues e enviar pull requests para melhorias neste projeto.

## Licença

Este projeto está licenciado sob a licença MIT. Veja o arquivo LICENSE para mais detalhes.
