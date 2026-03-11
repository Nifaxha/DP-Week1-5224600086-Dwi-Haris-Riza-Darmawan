# Task 1 — Balatro-Like Run Loop

**Mata Kuliah: Design Pattern for Games**

---

## Cara Build & Jalankan

```bash
g++ -std=c++17 main.cpp RunSession.cpp -o balatro_run
./balatro_run
```

## Struktur File

```
Task1/
├── main.cpp
├── RunSession.h / RunSession.cpp   ← pengontrol invariant loop
├── TurnInput.h                     ← struct data input
├── IInputGenerator.h               ← interface
├── FixedInputGenerator.h           ← implementasi awal
├── RandomInputGenerator.h          ← Modifikasi 1
├── IScoringRule.h                  ← interface
├── BasicScoringRule.h              ← implementasi scoring
├── IRewardRule.h                   ← interface
├── BonusRewardRule.h               ← Modifikasi 2
└── ShopSystem.h                    ← kelas konkret (tidak butuh interface)
```

---

## Keputusan Penggunaan Interface

| Komponen          | Interface? | Alasan                                                                   |
| ----------------- | ---------- | ------------------------------------------------------------------------ |
| `IInputGenerator` | ✅ Ya      | Ada 2 implementasi (Fixed & Random) — inti Modifikasi 1                  |
| `IScoringRule`    | ✅ Ya      | Formula scoring bersifat mutable, bisa diganti tanpa sentuh `RunSession` |
| `IRewardRule`     | ✅ Ya      | Inti Modifikasi 2 — reward harus bisa diganti bebas                      |
| `ShopSystem`      | ❌ Tidak   | Hanya satu implementasi, tidak perlu polimorfisme                        |
| `TurnInput`       | ❌ Tidak   | Struct data murni, bukan behavior                                        |

---

## Step 1 — Core Loop

Program ini mensimulasikan run 3 ronde dengan urutan fase berikut:

1. Bangkitkan input (nilai kartu)
2. Hitung base score dari input
3. Hitung reward dari base score
4. Perbarui uang pemain
5. Fase toko
6. Lanjut ke ronde berikutnya

Urutan ini diulang setiap ronde selama 3 ronde.

---

## Step 2 — Identifikasi Invariant

Urutan berikut **tidak boleh berubah**:

1. Generate input
2. Compute base score
3. Compute reward
4. Update money
5. Shop phase
6. Advance round

Jika urutan ini berubah, logika program akan rusak. Contohnya:

1. Jika reward dihitung sebelum base score, hasilnya tidak valid karena base score belum ada.
2. Jika uang diperbarui sebelum reward dihitung, jumlahnya akan salah.
3. Jika toko dibuka sebelum uang diperbarui, pemain belum punya uang untuk belanja.

**Komponen yang wajib ada:**

1. `RunSession` — pengontrol loop dan urutan fase
2. `IInputGenerator` — pembangkit nilai input
3. `IScoringRule` — penghitung base score
4. `IRewardRule` — penghitung reward
5. `ShopSystem` — fase toko

---

## Step 3 — Elemen Mutable

Berikut bagian-bagian yang bersifat mutable:

1. **Generator input**
   Bisa diganti dari `FixedInputGenerator` ke `RandomInputGenerator`. `RunSession` tidak berubah
   karena hanya bergantung pada interface `IInputGenerator`.

2. **Formula scoring**
   `BasicScoringRule` menghitung `score = input.value`. Bisa diganti menjadi formula lain
   tanpa menyentuh `RunSession`.

3. **Formula reward**
   `BonusRewardRule` membuat reward berbeda tergantung paritas ronde. Ini bisa diubah bebas
   selama implementasi `IRewardRule`.

4. **Isi toko dan harga**
   `ShopSystem` bisa diubah kontennya tanpa memengaruhi urutan fase.

Semua elemen ini bersifat mutable karena mengubah **perilaku numerik**, bukan **urutan struktural**.

---

## Refleksi

### 1. Apa struktur invariant dalam program ini?

Struktur invariant adalah **urutan fase yang dijaga di dalam `RunSession::RunRound()`**:

```
Generate Input → Compute Score → Compute Reward → Update Money → Shop → Advance Round
```

Urutan ini tidak boleh berubah. `RunSession` hanya mengontrol urutan ini — tidak ada logika
scoring, reward, maupun toko di dalamnya.

### 2. Bagian mana yang bersifat mutable?

Semua yang diinjeksikan melalui interface bersifat mutable: cara input dibangkitkan
(`IInputGenerator`), cara skor dihitung (`IScoringRule`), dan cara reward dihitung
(`IRewardRule`). Isi toko dan harga juga mutable karena terisolasi di dalam `ShopSystem`.

### 3. Ketika `InputGenerator` diganti, kenapa `RunSession` tidak berubah?

Karena `RunSession` hanya bergantung pada interface `IInputGenerator`, bukan pada kelas
konkretnya. Ia memanggil `generator_->Generate()` dan menerima `TurnInput` — tidak peduli
apakah nilai berasal dari angka tetap atau `std::rand()`. Kontraknya (interface) tetap sama,
sehingga `RunSession` tidak punya alasan untuk berubah.

### 4. Apa yang terjadi jika logika scoring diletakkan di dalam `RunSession`?

`RunSession` akan menjadi rapuh dan sulit dikembangkan. Setiap kali formula scoring perlu
diganti, kelas sesi harus dimodifikasi. Ini melanggar prinsip Single Responsibility —
`RunSession` seharusnya hanya mengontrol urutan fase, bukan mengandung logika scoring.
