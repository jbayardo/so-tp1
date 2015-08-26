import os

for fname in os.listdir('ejercicios'):
    fpath = 'ejercicios/'+fname

    if not os.isfile(fpath) or not fname[-3:] == 'tsk':
        continue

    # Es un archivo, y termina en tsk.
    matches = re.match('([A-Za-z0-9]+) ([0-9]+) ([0-9]+) ([0-9]+) ([A-Za-z0-9]+)_?(.*)?\.tsk')

    name = matches.group(0)

    command = './src/simusched {path} {cores} {costo_cs} {costo_mi} {sched} {params} | ./src/graphsched.py > {output}'.format(
            path = fpath,
            cores = matches.group(1),
            costo_cs = matches.group(2),
            costo_mi = matches.group(3),
            sched = matches.group(4),
            params = matches.group(5),
            output = 'ejercicios/' + name + '.png')

    os.system(command)


