import pygame
import sys
import subprocess
import platform

coordenadas = [
    {
        'name': 'E1',
        'coordenada': (37, 238)
    },
    {
        'name': 'E2',
        'coordenada': (195, 278)
    },
    {
        'name': 'E3',
        'coordenada': (329, 312)
    },
    {
        'name': 'E4',
        'coordenada': (433, 336)
    },
    {
        'name': 'E5',
        'coordenada': (619, 397)
    },
    {
        'name': 'E6',
        'coordenada': (645, 425)
    },
    {
        'name': 'E7',
        'coordenada': (591, 416)
    },
    {
        'name': 'E8',
        'coordenada': (461, 177)
    },
    {
        'name': 'E9',
        'coordenada': (329, 196)
    },
    {
        'name': 'E10',
        'coordenada': (157, 306)
    },
    {
        'name': 'E11',
        'coordenada': (220, 76)
    },
    {
        'name': 'E12',
        'coordenada': (460, 98)
    },
    {
        'name': 'E13',
        'coordenada': (395, 466)
    },
    {
        'name': 'E14',
        'coordenada': (368, 524)
    },
]

# Inicializa o Pygame
pygame.init()

# Configura a largura e altura da janela
largura, altura = 800, 600
screen = pygame.display.set_mode((largura, altura))

# Define o título da janela
pygame.display.set_caption('Problema do metro de Paris com A*')

# Carrega a imagem de fundo
background = pygame.image.load('./Interface/metro-map.png')

# Redimensiona a imagem de fundo para caber na janela (opcional)
background = pygame.transform.scale(background, (largura, altura))

# Define a cor da fonte (RGB)
font_color = (255, 0, 0)
# Define a cor do círculo (RGB)
circle_color = (255, 255, 255)
# Define a cor da borda do círculo (RGB)
border_color = (0, 0, 0)
# Define a cor do círculo quando clicado (RGB)
clicked_circle_color = (255, 0, 0)
# Define o raio do círculo e a espessura da borda
circle_radius = 10
border_thickness = 2

# Lista para armazenar o estado de clique dos círculos
clicked_states = [False] * len(coordenadas)
# Lista para armazenar os círculos clicados
clicked_circles = []

# Define as dimensões do botão
button_width = 120
button_height = 40
# Define a cor do botão
button_color = (0, 128, 0)
button_hover_color = (0, 255, 0)
# Define a cor do texto do botão
button_text_color = (255, 255, 255)

metro_path_coordenadas = []
executed = False

def clear_selection():
    global clicked_states, clicked_circles
    clicked_states = [False] * len(coordenadas)
    clicked_circles = []
    global executed
    executed = False

    # Limpa as coordenadas das linhas
    metro_path_coordenadas.clear()
    print("Seleção limpa.")

def get_coordenadas(metro_path):
    global metro_path_coordenadas

    for i in range(len(metro_path) - 1):

        for coordenada in coordenadas:
            if coordenada['name'] == metro_path[i]:
                start_coord = coordenada['coordenada']
                break
        for coordenada in coordenadas:
            if coordenada['name'] == metro_path[i + 1]:
                end_coord = coordenada['coordenada']
                break
        metro_path_coordenadas.append((start_coord, end_coord))

    global executed
    executed = True

    return metro_path_coordenadas

# Função a ser chamada quando o botão for clicado
def button_function(clicked_circles):
    if platform.system() == 'Windows':
        exe_path = "../Algoritmo/output/Main.exe"
    elif platform.system() == 'Linux':
        exe_path = "./Algoritmo/output/Main"
    else:
        print("Sistema operacional não suportado.")
        # Encerra o programa com um código de erro
        exit(1) 

    # Argumentos a serem passados para o executável
    args = []
    for circle in clicked_circles:
        args.append(circle['name'])
    print(args)

    metro_path = []
    try:
        result = subprocess.run(
            [exe_path] + args, 
            capture_output=True, 
            text=True, 
            check=True
        )
        print(result.returncode)
        metro_path = result.stdout.split(',')
        print("Saída:", metro_path)
    except subprocess.CalledProcessError as e:
        if(e.returncode == 19):
            message = f"Não existe rota entre as estações {args}!"
            print(message)
        elif(e.returncode == 20):
            message = f"Não foi possível encontrar um caminho!"
            print(message)
        else:
            print(f"Erro ao executar o arquivo: {e}")

    # Coordenadas específicas para conectar com linhas
    get_coordenadas(metro_path)

# Loop principal do jogo
running = True
while running:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False
        elif event.type == pygame.MOUSEBUTTONDOWN:
            # Pega a posição do clique do mouse
            click_pos = pygame.mouse.get_pos()

            # Verifica se o clique está dentro de um círculo
            for i, coord in enumerate(coordenadas):
                if len(clicked_circles) < 2 or clicked_states[i]:
                    # Verifica se o clique está dentro do círculo
                    distancia = ((click_pos[0] - coord['coordenada'][0]) ** 2 + (click_pos[1] - coord['coordenada'][1]) ** 2) ** 0.5
                    if distancia <= circle_radius + border_thickness:
                        clicked_states[i] = not clicked_states[i]  # Alterna o estado de clique
                        if clicked_states[i]:
                            if coord not in clicked_circles:
                                clicked_circles.append(coord)
                        else:
                            if coord in clicked_circles:
                                clicked_circles.remove(coord)
                        # Imprime os círculos clicados no console
                        print("Círculos clicados:", clicked_circles)


            # Verifica se o clique está dentro dos botões
            if clear_button_rect.collidepoint(click_pos):
                clear_selection()
            elif button_rect.collidepoint(click_pos):
                button_function(clicked_circles)

            

    # Pega a posição do mouse na tela
    mouse_pos = pygame.mouse.get_pos()

    # Desenha a imagem de fundo
    screen.blit(background, (0, 0))

    # Desenha o caminho
    if executed:
        for start_coord, end_coord in metro_path_coordenadas:
            pygame.draw.line(screen, (255, 0, 0), start_coord, end_coord, 15)

    # Desenha a posição do mouse relativa à imagem na tela
    # font = pygame.font.Font(None, 36)
    # text = font.render(f'Mouse: {mouse_pos}', True, font_color)
    # screen.blit(text, (10, 10))

    for i, coord in enumerate(coordenadas):
        # Define a cor do círculo com base no estado de clique
        current_circle_color = clicked_circle_color if clicked_states[i] else circle_color
        # Desenha um círculo com borda na posição especificada
        pygame.draw.circle(screen, border_color, coord['coordenada'], circle_radius + border_thickness)
        pygame.draw.circle(screen, current_circle_color, coord['coordenada'], circle_radius)

    # Desenha o botão Executar
    button_rect = pygame.Rect(
        largura - button_width - 10, 
        altura - button_height - 10, 
        button_width, 
        button_height
    )
    if button_rect.collidepoint(mouse_pos):
        pygame.draw.rect(screen, button_hover_color, button_rect)
    else:
        pygame.draw.rect(screen, button_color, button_rect)

    button_font = pygame.font.Font(None, 36)
    button_text = button_font.render("Executar", True, button_text_color)
    button_text_rect = button_text.get_rect(center=button_rect.center)
    screen.blit(button_text, button_text_rect)

    # Desenha o botão Limpar
    clear_button_rect = pygame.Rect(
        10,
        altura - button_height - 10,
        button_width, 
        button_height
    )

    # Desenha o botão Limpar Seleção
    if clear_button_rect.collidepoint(mouse_pos):
        pygame.draw.rect(screen, button_hover_color, clear_button_rect)
    else:
        pygame.draw.rect(screen, button_color, clear_button_rect)

    button_font = pygame.font.Font(None, 36)
    button_text = button_font.render("Limpar", True, button_text_color)
    button_text_rect = button_text.get_rect(center=clear_button_rect.center)
    screen.blit(button_text, button_text_rect)

    # Atualiza o display
    pygame.display.flip()

# Encerra o Pygame
pygame.quit()
sys.exit()
