### Factory Method

1. **意图**
    > 定义一个用于创建对象的接口，让子类决定应该实例化哪一个类。Factory Method 使一个类的实例化延迟到其子类。

2. **适用性**
    - 当一个类不知道它所必须创建的对象的类的时候。
    - 当一个类希望由它的子类来指定它所创建的对象的时候。

3. **实现**
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