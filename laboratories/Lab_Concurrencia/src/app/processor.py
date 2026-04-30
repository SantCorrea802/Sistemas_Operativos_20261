import random
import time

from app.repository import Task


def process_task(task: Task) -> str:
    
    #Simula procesamiento independiente El sleep aleatorio ayuda a evidenciar concurrencia: los workers terminan en orden intercalado
    
    time.sleep(random.uniform(0.3, 1.8))
    

    
    
    return f"processed({task.description})"