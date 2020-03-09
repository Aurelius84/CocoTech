### Abstract Factory

1. **意图**
    > 提供一个创建相关或者相互依赖对象的接口，而无需指定它们具体的类。

2. **适用性**
    - 当一个系统独立与它的产品的创建、组合和表示时
    - 当一个系统需要多个产品系列中的一个来配置时
    - 当强调一系列相关的产品对象的设计以便进行联合使用时
    - 当提供一个产品类库，而只想显示它们的接口而不是实现时。

3. **实现**
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