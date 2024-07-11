from ultralytics import YOLO
import cv2


def train_model(data_path, model_name='yolov8n-cls.pt', epochs=10):
    model = YOLO(model_name)

    result = model.train(
        data=data_path,
        epochs=epochs
    )
    print(result)

    model_path = 'yolov8n-cls-training.pt'
    model.save(model_path)

    return model_path


def classify_image(model_path, image_path):
    model = YOLO(model_path)

    image = cv2.imread(image_path)
    if image is None:
        raise FileNotFoundError(f"Image not found: {image_path}")

    results = model(image)

    return results


if __name__ == '__main__':
    model_name = train_model(data_path='../data', epochs=1)

    result = classify_image(
        'yolov8n-cls-training.pt',
        image_path='C:\\development\\Python\\neuralHemangiomas\\data\\test\\HM\\HMG (48).jpg'
    )

    print(result)
