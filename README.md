# DSP_HW3
Digital signal processing homework 3

# 과제 개요
이번 과제에서는 Gaussian filter를 사용하여 이미지의 다운샘플링과 업샘플링 과정에서 Antialiasing을 수행하고 이를 검증한다. 이미지의 Downsampling은 한 샘플링 과정에서 특정한 Phase를 골라 진행하고, Upsampling과정에서는 6-Tab DCT-IF 를 이용한 Upsampling을 진행한다.

# 과제 수행

이번 과제의 수행에는 크게 3가지 부분으로 나뉘어져 있다.
-	Antialiasing filtering with Gaussian filter
Gaussian filter로 Antialiasing을 한 이미지와 Antialiasing을 하지 않은 이미지를 각각 처리하여 Antialiasing에 대한 효과를 검증한다.
Gauaaisn Filter는 다음과 같이 구성하였다.
![image](https://user-images.githubusercontent.com/42211014/203699588-b4ad7224-07e0-48f6-9282-d4b5d08a62d6.png)

과제에서 제시한 형태와 같은 형태로 Gaussian Filter를 구성하였고 이 Filter를 사용하여 2d convolution 연산을 수행하여 Filtering을 수행할 수 있다.

-	Downsampling
Downsampling은 Phase(샘플링 주기) 내에서 특정한 위치에 있는 pixel만을 골라 진행하였다. 또한 Downsampling을 진행하고 Antialiasing이 되지 않은 이미지와 Gaussian Filter에 의한 Antialiasing이 적용된 이미지를 비교할 수 있었다.

-	Upsampling and Measure MSE
Upsampling은 6-Tab DCT-IF 를 사용사여 진행하였다. DCT-IF의 특징으로는 변환 전에 여기저기 분포되어 있던 것이 변환 후에 이웃 화소 간에 거의 차이가 없는 Low-Frequency항목으로 변환되게 한다. 이에 대한 구현은 Reconstruction method에서 DCT 연산을 수행하는 함수를 호출하는 것으로 구현하였다.
MSE의 측정은 원본 이미지와 Antialiased된 이미지, 원본 이미지와 Downsampling – Upsampling 된 이미지 각각 두 번 씩 측정하였다.

# 과제 수행 결과
![image](https://user-images.githubusercontent.com/42211014/203699642-5dd2491b-a957-4100-b431-bc03c8ba3d77.png)

과제 수행 결과 MSE를 각각 측정하여 콘솔에 표시하였다. 결과적으로 Antialiased image의 MSE가 낮게 측정되는 것을 알 수 있었다. 이미지의 MSE는 낮을수록 원본에 가까운 이미지이다.
아래는 이미지의 변환 결과이다.

![image](https://user-images.githubusercontent.com/42211014/203699665-35ad610f-43f1-491b-a3e2-598c89502876.png)
Antialiased되지 않은 downsampling처리 된 이미지

![image](https://user-images.githubusercontent.com/42211014/203699734-6cf5da2a-513a-4749-97d8-1955a2d52dab.png)
Antialiased된 Downdampled처리 이미지

![image](https://user-images.githubusercontent.com/42211014/203699795-65dc5539-054d-4d6e-8b64-e3e3093b7365.png)

Antialiased되지 않은 Reconstruction 이미지

![image](https://user-images.githubusercontent.com/42211014/203699863-9ba93574-2a19-44ed-b0c1-65196eddabcb.png)
Antialiased된 Reconstruction 이미지

차례대로 위부터 Antialiased 되지 않은 downsampling image, antialiased된 downsampling 이미지. Antialiased 되지 않은 reconstructed image, Antialiased된 reconstruced 이미지이고, 육안으로 봐서는 차이를 느끼기는 쉽지 않아 보인다. 하지만 자세한 디테일을 보면 세부적으로 다른 모습이 느껴지고, MSE의 측정 결과를 보아서는 Antialiased된 이미지의 MSE가 더 낮게 나오는 것을 보아 원본 이미지에 더 가까운 이미지는 Antialiased된 이미지 쪽이었다.

이외에도 5개의 이미지를 연속적으로 변환하여 테스트해 보았고, 5개 이미지 모두 Antialiasing이 적용된 이미지의 MSE가 더 낮게 나오는 것을 알 수 있었다.


# 고찰
이번 과제에서 가장 힘들었던 부분은 DCT-IF를 구현하는 부분이었다. 처음에는 padding한 부분에 대하여 DCT변환을 할 때 padding에 대한 부분에 대해서도 결과를 구해야 하는 것으로 생각하여 힘들었지만 조금 생각해본 뒤 Downsampling된 이미지로부터 각 pixel의 추측 값을 구하는 것으로 구현하였는데 정상적으로 작동하였다.
그리고 이전 과제에서는 Main함수에 전부 구현하여 code가 복잡하였는데 이번에는 그러한 부분을 개선하였고, 여러 파일을 순차적으로 읽어 처리할 수 있도록 하였다. 
