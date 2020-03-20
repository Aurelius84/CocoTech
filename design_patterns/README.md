## 1.常见的三种最基本的设计模式
1. **创建模式**
   
   提供实例化的方法，为适合的情况提供相应的创建方法。
   
2. **结构化模式**

   用于处理实体之间的关系，使得这些实体可以更好的协同工作。

3. **行为模式**
   
   用于不同的实体进行通信，为实体之间的通信提供更容易、更灵活的同你方法。

## 2.详细的模式介绍
### 2.1 创建型

#### Factory Method (工厂方法)

<div align=center>![Factory Method](https://raw.githubusercontent.com/Aurelius84/CocoTech/master/design_patterns/img/factory_method.jpeg)</div>
1. **作用**
    > 定义一个用于创建对象的接口，让子类决定应该实例化哪一个类。Factory Method 使一个类的实例化延迟到其子类。

2. **适用场景**
    - 当一个类不知道它所必须创建的对象的类的时候。
    - 当一个类希望由它的子类来指定它所创建的对象的时候。

3. **样例Demo**
    ```python
    class ChinaGetter(object):
        def __init__(self):
            self.trans = dict(dog='小狗',cat='小猫')

        def get(self, msg_id):
            try:
                return self.trans[msg_id]
            except KeyError:
                return str(msg_id)

    class EnglishGetter(object):
        def get(self, msg_id):
            return str(msg_id)

    def get_localizer(language='English'):
        languages = dict(English=EnglishGetter, China=ChinaGetter)
        return languages[language]()

    # create localizer
    e, g = get_localizer('English'), get_localizer('China')
    for text in "A cat sits on the desk".split():
        print(e.get(text), g.get(text))
    ```

#### Abstract Factory (抽象工厂)

1. **作用**
    > 提供一个创建相关或者相互依赖对象的接口，而无需指定它们具体的类。

2. **适用场景**
    - 当一个系统独立与它的产品的创建、组合和表示时
    - 当一个系统需要多个产品系列中的一个来配置时
    - 当强调一系列相关的产品对象的设计以便进行联合使用时
    - 当提供一个产品类库，而只想显示它们的接口而不是实现时。

3. **样例Demo**
    ```python
    import random

    class Cat(object):
        def speak(self):
            return 'meow'

        def __str__(self):
            return 'Cat'

    class Dog(object):
        def speak(self):
            return 'woolf'

        def __str__(self):
            return 'Dog'

    class CatFactory(object):
        def get_pet(self):
            return Cat()

        def get_food(self):
            return 'Cat food'

    class DogFactory(object):
        def get_pet(self):
            return Dog()

        def get_food(self):
            return 'Dog food'

    class PetShop(object):
        def __init__(self, animal_factory=None):
            self.factory = animal_factory

        def show_pet(self):
            pet = self.factory.get_pet()
            print('This is a lovely ', str(pet))
            print('pet speaks ', pet.speak())
            print('pet eats ', pet.get_food())

    def get_factory():
        return random.choice([DogFactory, CatFactory])
    ```
