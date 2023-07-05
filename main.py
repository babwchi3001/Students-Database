import random
from datetime import datetime

names = ['Emma', 'Olivia', 'Ava', 'Isabella', 'Sophia', 'Mia', 'Charlotte', 'Amelia', 'Harper', 'Evelyn','Abigail', 'Emily', 'Elizabeth', 'Avery', 'Sofia', 'Ella', 'Madison', 'Scarlett', 'Victoria', 'Aria','Grace', 'Chloe', 'Camila', 'Penelope', 'Riley', 'Layla', 'Lillian', 'Natalie', 'Hazel', 'Brooklyn',         'Addison', 'Makayla', 'Audrey', 'Gabriella', 'Savannah', 'Aubrey', 'Aaliyah', 'Aurora', 'Kaylee', 'Avery',         'Arianna', 'Aria', 'Genesis', 'Eva', 'Lila', 'Naomi', 'Caroline', 'Ruby', 'Kennedy', 'Paisley','Alexa', 'Bella', 'Autumn', 'Clara', 'Eleanor', 'Violet', 'Adeline', 'Stella', 'Lucy', 'Maya',         'Ellie', 'Jasmine', 'Nova', 'Trinity', 'Kinsley', 'Delilah', 'Valentina', 'Willow', 'Ivy', 'Liliana',         'Jade', 'Hope', 'Madelyn', 'Gracie', 'Kiara', 'Melanie', 'Isla', 'Luna', 'Fiona', 'Makenna',         'Giselle', 'Hadley', 'Camille', 'Aubree', 'Aniyah', 'Fatima', 'Gia', 'Josephine', 'Vivienne', 'Reagan',         'Raelynn', 'Leilani', 'Mariah', 'Paris', 'Hayden', 'Alicia', 'Harmony', 'Adalyn', 'Katherine', 'Summer',         'Lena', 'Gemma', 'Nora', 'Eliana', 'Brianna', 'Sienna', 'Lilah', 'Gwendolyn', 'Margaret', 'Daphne']

surnames = ['Smith', 'Johnson', 'Williams', 'Jones', 'Brown', 'Davis', 'Miller', 'Wilson', 'Moore', 'Taylor','Anderson', 'Thomas', 'Jackson', 'White', 'Harris', 'Martin', 'Thompson', 'Young', 'Allen', 'King','Wright', 'Scott', 'Green', 'Baker', 'Adams', 'Nelson', 'Carter', 'Mitchell', 'Perez', 'Roberts','Robinson', 'Clark', 'Rodriguez', 'Lewis', 'Lee', 'Walker', 'Hall', 'Allen', 'Young', 'Hernandez','Lopez', 'Hill', 'Sanchez', 'Morris', 'Rogers', 'Reed', 'Cook', 'Bailey', 'Bell', 'Cooper',            'Richardson', 'Cox', 'Howard', 'Ward', 'Torres', 'Peterson', 'Gray', 'Ramirez', 'James', 'Watson',            'Garcia', 'Martinez', 'Rodriguez', 'Hernandez', 'Lopez', 'Gonzalez', 'Perez', 'Taylor', 'Anderson', 'Wilson',            'Moore', 'Gomez', 'Campbell']

rand_nr = random.randint(1, 5)
with open("school.txt", "w") as file:
    random.seed(datetime.now().timestamp())
    print(rand_nr)
    counter = 1
    for i in range(rand_nr):
        file.write(str(counter) + " 4 " + "4 " + "4" + "\n")
        counter = counter + 1

student_info = []
fullnames = []
fullnames_random = []
for name in names:
    for surname in surnames:
        fullname = name + " " + surname
        if fullname not in fullnames:
            new_rand = random.randint(2000, 2002)
            grade = random.randint(0, 20000)
            counter = random.randint(1, rand_nr)
            fullnames.append(fullname)
            s_info = fullname + "  " + str(counter) + " " + str(new_rand) + " " + str(grade) +"\n"
            student_info.append(s_info)

#for rand_name in student_info:
#    something = random.choice(student_info)
#    fullnames_random.append(something)
#    student_info.remove(something)
#
#print(student_info)

while student_info:
    rand_name = random.choice(student_info)
    fullnames_random.append(rand_name)
    student_info.remove(rand_name)



with open("names_surnames.txt", "w") as file:
    for info in fullnames_random:
        file.write(info)
