# Jogo Ping Pongo

# Descrição
* Desenvolvemos um jogo simples de ping pong cujo objetivo é arremessar a caixa a partir da base e
* acertar os jarros suspensos. As colisões permitidas são somente na base do jarro, ou seja, a caixa
* só irá quebrar o jarro se acertar exatamente na parte de baixo do jarro. Foi adicionado efeitos sonoros
* para deixar o jogo mais dinâmico. A cada 5 arremessos da caixa a partir da base, o arremesso da caixa
* fica levemente mais rápida que, com o passar do tempo, será impossível acertar a caixa na base.

# Controles (sem caps lock):
* 'a': move para esquerda
* 'd': move para direita
* 'w': move para cima
* 's': move para baixo

# Descrição do desenvolvimento
* O jogo foi inteiramente desenvolvido em C++ utilizando as bibliotecas GLUT para os efeitos gráficos, 
* windows para utilizarmos a biblioteca de som do windows com facilidade, mmsystem que permite usar sons no jogo, 
* stb_image que faz importação de texturas e glm que importa objetos 3d no projeto.

# Instruções para executar o projeto
* Tenha as bibliotecas citadas no tópico anterior instaladas na sua máquina. Utilizamos a IDE Falcon C++ e através dela
* é mais fácil de inserir as bibliotecas inseridas. Desenvolvemos usando o SO Windows 10. Tendo essas configurações respeitadas
* baixe este repositório para uma pasta do seu computador e execute o arquivo "pingpong.fpj" no Falcon C++. Ele irá abrir
* o projeto, com o código-fonte escrito. Caso queira recompilar o projeto, no Falcon C++ precione o botão f9 ou procure
* a opção compilar e executar. Caso não queira recompilar, procure o arquivo "pingpong.exe" na pasta do repositório do jogo e o execute.

# Contribuintes
* [Filipe Alves Sampaio](https://github.com/filipeas)
* [Lucas Hiago de Moura Vilela](https://github.com/luchiago)